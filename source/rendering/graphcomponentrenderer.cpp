#include "graphcomponentrenderer.h"

#include "camera.h"
#include "primitives/quad.h"
#include "material.h"

#include "../graph/graphmodel.h"
#include "../layout/layout.h"
#include "../layout/barneshuttree.h"
#include "../layout/collision.h"

#include "../maths/frustum.h"
#include "../maths/plane.h"
#include "../maths/boundingsphere.h"

#include "../ui/graphwidget.h"
#include "../ui/selectionmanager.h"

#include "../utils/utils.h"
#include "../utils/make_unique.h"

#include <QObject>
#include <QOpenGLContext>
#include <QOpenGLFunctions_3_3_Core>

#include <QKeyEvent>
#include <QMouseEvent>

#include <QtMath>
#include <cmath>
#include <mutex>

static void setupCamera(Camera& camera, float fovy, float aspectRatio)
{
    camera.setPerspectiveProjection(fovy, aspectRatio, 0.3f, 50000.0f);
}

static bool loadShaderProgram(QOpenGLShaderProgram& program, const QString& vertexShader, const QString& fragmentShader)
{
    if(!program.addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShader))
    {
        qCritical() << QObject::tr("Could not compile vertex shader. Log:") << program.log();
        return false;
    }

    if(!program.addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShader))
    {
        qCritical() << QObject::tr("Could not compile fragment shader. Log:") << program.log();
        return false;
    }

    if(!program.link())
    {
        qCritical() << QObject::tr("Could not link shader program. Log:") << program.log();
        return false;
    }

    return true;
}

GraphComponentRendererShared::GraphComponentRendererShared(const QOpenGLContext& context) :
    _context(&context)
{
    loadShaderProgram(_screenShader, ":/rendering/shaders/screen.vert", ":/rendering/shaders/screen.frag");
    loadShaderProgram(_selectionShader, ":/rendering/shaders/screen.vert", ":/rendering/shaders/selection.frag");

    loadShaderProgram(_nodesShader, ":/rendering/shaders/instancednodes.vert", ":/rendering/shaders/ads.frag");
    loadShaderProgram(_edgesShader, ":/rendering/shaders/instancededges.vert", ":/rendering/shaders/ads.frag");

    loadShaderProgram(_selectionMarkerShader, ":/rendering/shaders/2d.vert", ":/rendering/shaders/selectionMarker.frag");
    loadShaderProgram(_debugLinesShader, ":/rendering/shaders/debuglines.vert", ":/rendering/shaders/debuglines.frag");
}

GraphComponentRenderer::GraphComponentRenderer()
    : _graphWidget(nullptr),
      _initialised(false),
      _visible(false),
      _frozen(false),
      _cleanupWhenThawed(false),
      _updateVisualDataWhenThawed(false),
      _updatePositionDataWhenThawed(false),
      _width(0), _height(0),
      _colorTexture(0),
      _selectionTexture(0),
      _depthTexture(0),
      _visualFBO(0),
      _FBOcomplete(false),
      _visualDataRequiresUpdate(false),
      _trackFocus(true),
      _targetZoomDistance(0.0f),
      _funcs(nullptr),
      _aspectRatio(0.0f),
      _fovx(0.0f),
      _fovy(0.0f),
      _numNodesInPositionData(0),
      _numEdgesInPositionData(0)
{
}

void GraphComponentRenderer::initialise(std::shared_ptr<GraphModel> graphModel, ComponentId componentId,
                                        GraphWidget& graphWidget,
                                        std::shared_ptr<SelectionManager> selectionManager,
                                        std::shared_ptr<GraphComponentRendererShared> shared)
{
    _graphModel = graphModel;
    _componentId = componentId;
    _graphWidget = &graphWidget;
    _selectionManager = selectionManager;
    _shared = shared;

    _funcs = _shared->_context->versionFunctions<QOpenGLFunctions_3_3_Core>();
    if(!_funcs)
        qFatal("Could not obtain required OpenGL context version");
    _funcs->initializeOpenGLFunctions();

    //FIXME: eliminate Material, set shader directly?
    MaterialPtr nodeMaterial(new Material);
    nodeMaterial->setShaders(":/rendering/shaders/instancednodes.vert", ":/rendering/shaders/ads.frag");

    _sphere.setRadius(1.0f);
    _sphere.setRings(16);
    _sphere.setSlices(16);
    _sphere.setMaterial(nodeMaterial);
    _sphere.create();

    MaterialPtr edgeMaterial(new Material);
    edgeMaterial->setShaders(":/rendering/shaders/instancededges.vert", ":/rendering/shaders/ads.frag");

    _cylinder.setRadius(1.0f);
    _cylinder.setLength(1.0f);
    _cylinder.setSlices(8);
    _cylinder.setMaterial(edgeMaterial);
    _cylinder.create();

    if(!_debugLinesDataVAO.isCreated())
        _debugLinesDataVAO.create();

    if(!_selectionMarkerDataVAO.isCreated())
        _selectionMarkerDataVAO.create();

    prepareVertexBuffers();

    prepareNodeVAO();
    prepareEdgeVAO();
    prepareSelectionMarkerVAO();
    prepareDebugLinesVAO();
    prepareQuad();

    setupCamera(_viewData._camera, _fovy, _aspectRatio);
    _targetZoomDistance = _viewData._zoomDistance;
    _viewData._focusNodeId.setToNull();

    _initialised = true;

    updatePositionalData();
    updateVisualData(When::Now);
}

void GraphComponentRenderer::cleanup()
{
    if(_frozen)
    {
        _cleanupWhenThawed = true;
        return;
    }

    if(_visualFBO != 0)
    {
        _funcs->glDeleteFramebuffers(1, &_visualFBO);
        _visualFBO = 0;
    }

    _FBOcomplete = false;

    if(_colorTexture != 0)
    {
        _funcs->glDeleteTextures(1, &_colorTexture);
        _colorTexture = 0;
    }

    if(_selectionTexture != 0)
    {
        _funcs->glDeleteTextures(1, &_selectionTexture);
        _selectionTexture = 0;
    }

    if(_depthTexture != 0)
    {
        _funcs->glDeleteTextures(1, &_depthTexture);
        _depthTexture = 0;
    }

    _nodePositionData.clear();
    _numNodesInPositionData = 0;
    _edgePositionData.clear();
    _numEdgesInPositionData = 0;

    _nodeVisualData.clear();
    _edgeVisualData.clear();

    _graphModel = nullptr;
    _componentId.setToNull();
    _graphWidget = nullptr;
    _selectionManager = nullptr;
    _shared = nullptr;

    _funcs = nullptr;
    _initialised = false;
}

void GraphComponentRenderer::cloneViewDataFrom(const GraphComponentRenderer& other)
{
    _viewData = other._viewData;
}

void GraphComponentRenderer::freeze()
{
    _frozen = true;
}

void GraphComponentRenderer::thaw()
{
    _frozen = false;

    if(_updateVisualDataWhenThawed)
    {
        updateVisualData(When::Now);
        _updateVisualDataWhenThawed = false;
    }

    if(_updatePositionDataWhenThawed)
    {
        updatePositionalData();
        _updatePositionDataWhenThawed = false;
    }

    if(_cleanupWhenThawed)
    {
        cleanup();
        _cleanupWhenThawed = false;
    }
}

void GraphComponentRenderer::updatePositionalData()
{
    Q_ASSERT(_initialised);

    if(_frozen)
    {
        _updatePositionDataWhenThawed = true;
        return;
    }

    std::unique_lock<std::recursive_mutex> lock(_graphModel->nodePositions().mutex());

    auto component = _graphModel->graph().componentById(_componentId);

    NodePositions& nodePositions = _graphModel->nodePositions();

    _numNodesInPositionData = component->numNodes();
    _numEdgesInPositionData = component->numEdges();

    _nodePositionData.resize(_numNodesInPositionData * 3);
    _edgePositionData.resize(_numEdgesInPositionData * 6);
    int i = 0;

    NodeArray<QVector3D> scaledAndSmoothedNodePositions(_graphModel->graph());

    for(NodeId nodeId : component->nodeIds())
    {
        const QVector3D nodePosition = nodePositions.getScaledAndSmoothed(nodeId);
        scaledAndSmoothedNodePositions[nodeId] = nodePosition;

        _nodePositionData[i++] = nodePosition.x();
        _nodePositionData[i++] = nodePosition.y();
        _nodePositionData[i++] = nodePosition.z();
    }

    _nodePositionBuffer.bind();
    _nodePositionBuffer.allocate(_nodePositionData.data(), static_cast<int>(_nodePositionData.size()) * sizeof(GLfloat));
    _nodePositionBuffer.release();

    i = 0;
    for(EdgeId edgeId : component->edgeIds())
    {
        const Edge& edge = _graphModel->graph().edgeById(edgeId);
        const QVector3D sourcePosition = scaledAndSmoothedNodePositions[edge.sourceId()];
        const QVector3D targetPosition = scaledAndSmoothedNodePositions[edge.targetId()];

        _edgePositionData[i++] = sourcePosition.x();
        _edgePositionData[i++] = sourcePosition.y();
        _edgePositionData[i++] = sourcePosition.z();
        _edgePositionData[i++] = targetPosition.x();
        _edgePositionData[i++] = targetPosition.y();
        _edgePositionData[i++] = targetPosition.z();
    }

    _edgePositionBuffer.bind();
    _edgePositionBuffer.allocate(_edgePositionData.data(), static_cast<int>(_edgePositionData.size()) * sizeof(GLfloat));
    _edgePositionBuffer.release();

    _viewData._focusPosition = NodePositions::centreOfMassScaled(_graphModel->nodePositions(),
                                                                 component->nodeIds());

    updateEntireComponentZoomDistance();
}

float GraphComponentRenderer::zoomDistanceForNodeIds(const QVector3D& centre, std::vector<NodeId> nodeIds)
{
    float minHalfFov = qDegreesToRadians(std::min(_fovx, _fovy) * 0.5f);

    if(minHalfFov > 0.0f)
    {
        float maxDistance = std::numeric_limits<float>::min();
        for(auto nodeId : nodeIds)
        {
            QVector3D nodePosition = _graphModel->nodePositions().getScaledAndSmoothed(nodeId);
            auto& nodeVisual = _graphModel->nodeVisuals().at(nodeId);
            float distance = (centre - nodePosition).length() + nodeVisual._size;

            if(distance > maxDistance)
                maxDistance = distance;
        }

        return maxDistance / std::sin(minHalfFov);
    }
    else
    {
        qWarning() << "zoomDistanceForNodes returning default value";
        return 1.0f;
    }
}

void GraphComponentRenderer::updateEntireComponentZoomDistance()
{
    auto component = _graphModel->graph().componentById(_componentId);
    _entireComponentZoomDistance = zoomDistanceForNodeIds(focusPosition(), component->nodeIds());
}

void GraphComponentRenderer::updateVisualData(When when)
{
    _visualDataRequiresUpdate = true;

    if(when == When::Now)
        updateVisualDataIfRequired();
}

void GraphComponentRenderer::updateVisualDataIfRequired()
{
    Q_ASSERT(_initialised);

    if(!_visualDataRequiresUpdate)
        return;

    if(_frozen)
    {
        _updateVisualDataWhenThawed = true;
        return;
    }

    auto component = _graphModel->graph().componentById(_componentId);

    _visualDataRequiresUpdate = false;

    auto& nodeVisuals = _graphModel->nodeVisuals();
    auto& edgeVisuals = _graphModel->edgeVisuals();

    _nodeVisualData.resize(component->numNodes() * 7);
    _edgeVisualData.resize(component->numEdges() * 7);

    const QColor selectedOutLineColor = Qt::GlobalColor::white;
    const QColor deselectedOutLineColor = Qt::GlobalColor::black;

    int i = 0;
    for(NodeId nodeId : component->nodeIds())
    {
        _nodeVisualData[i++] = nodeVisuals[nodeId]._size;
        _nodeVisualData[i++] = nodeVisuals[nodeId]._color.redF();
        _nodeVisualData[i++] = nodeVisuals[nodeId]._color.greenF();
        _nodeVisualData[i++] = nodeVisuals[nodeId]._color.blueF();

        QColor outlineColor = _selectionManager && _selectionManager->nodeIsSelected(nodeId) ?
            outlineColor = selectedOutLineColor :
            outlineColor = deselectedOutLineColor;

        _nodeVisualData[i++] = outlineColor.redF();
        _nodeVisualData[i++] = outlineColor.greenF();
        _nodeVisualData[i++] = outlineColor.blueF();
    }

    _nodeVisualBuffer.bind();
    _nodeVisualBuffer.allocate(_nodeVisualData.data(), static_cast<int>(_nodeVisualData.size()) * sizeof(GLfloat));
    _nodeVisualBuffer.release();

    i = 0;
    for(EdgeId edgeId : component->edgeIds())
    {
        _edgeVisualData[i++] = edgeVisuals[edgeId]._size;
        _edgeVisualData[i++] = edgeVisuals[edgeId]._color.redF();
        _edgeVisualData[i++] = edgeVisuals[edgeId]._color.greenF();
        _edgeVisualData[i++] = edgeVisuals[edgeId]._color.blueF();
        _edgeVisualData[i++] = deselectedOutLineColor.redF();
        _edgeVisualData[i++] = deselectedOutLineColor.greenF();
        _edgeVisualData[i++] = deselectedOutLineColor.blueF();
    }

    _edgeVisualBuffer.bind();
    _edgeVisualBuffer.allocate(_edgeVisualData.data(), static_cast<int>(_edgeVisualData.size()) * sizeof(GLfloat));
    _edgeVisualBuffer.release();
}

void GraphComponentRenderer::update(float t)
{
    Q_ASSERT(_initialised);

    if(_graphModel)
    {
        updateVisualDataIfRequired();

        _zoomTransition.update(t);

        if(_graphWidget->transition().finished() && _trackFocus)
        {
            if(trackingCentreOfComponent())
            {
                if(_zoomTransition.finished() && _viewData._autoZooming)
                    zoomToDistance(_entireComponentZoomDistance);

                centrePositionInViewport(_viewData._focusPosition, _viewData._zoomDistance);
            }
            else
                centreNodeInViewport(_viewData._focusNodeId, _viewData._zoomDistance);
        }

        _modelViewMatrix = _viewData._camera.viewMatrix();
        _projectionMatrix = _viewData._camera.projectionMatrix();
    }

    submitDebugLines();
}

static void setShaderADSParameters(QOpenGLShaderProgram& program)
{
    struct Light
    {
        Light() {}
        Light(const QVector4D& _position, const QVector3D& _intensity) :
            position(_position), intensity(_intensity)
        {}

        QVector4D position;
        QVector3D intensity;
    };

    std::vector<Light> lights;
    lights.emplace_back(QVector4D(-20.0f, 0.0f, 3.0f, 1.0f), QVector3D(0.6f, 0.6f, 0.6f));
    lights.emplace_back(QVector4D(0.0f, 0.0f, 0.0f, 1.0f), QVector3D(0.2f, 0.2f, 0.2f));
    lights.emplace_back(QVector4D(10.0f, -10.0f, -10.0f, 1.0f), QVector3D(0.4f, 0.4f, 0.4f));

    int numberOfLights = static_cast<int>(lights.size());

    program.setUniformValue("numberOfLights", numberOfLights);

    for(int i = 0; i < numberOfLights; i++)
    {
        QByteArray positionId = QString("lights[%1].position").arg(i).toLatin1();
        program.setUniformValue(positionId.data(), lights[i].position);

        QByteArray intensityId = QString("lights[%1].intensity").arg(i).toLatin1();
        program.setUniformValue(intensityId.data(), lights[i].intensity);
    }

    program.setUniformValue("material.ks", QVector3D(1.0f, 1.0f, 1.0f));
    program.setUniformValue("material.ka", QVector3D(0.1f, 0.1f, 0.1f));
    program.setUniformValue("material.shininess", 50.0f);
}

void GraphComponentRenderer::renderNodes()
{
    GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    _funcs->glDrawBuffers(2, drawBuffers);

    _shared->_nodesShader.bind();
    setShaderADSParameters(_shared->_nodesShader);

    _nodePositionBuffer.bind();
    _nodeVisualBuffer.bind();

    QMatrix3x3 normalMatrix = _modelViewMatrix.normalMatrix();
    _shared->_nodesShader.setUniformValue("modelViewMatrix", _modelViewMatrix);
    _shared->_nodesShader.setUniformValue("normalMatrix", normalMatrix);
    _shared->_nodesShader.setUniformValue("projectionMatrix", _projectionMatrix);

    // Draw the nodes
    _sphere.vertexArrayObject()->bind();
    _funcs->glDrawElementsInstanced(GL_TRIANGLES, _sphere.indexCount(),
                                    GL_UNSIGNED_INT, 0, _numNodesInPositionData);
    _sphere.vertexArrayObject()->release();

    _nodeVisualBuffer.release();
    _nodePositionBuffer.release();
    _shared->_nodesShader.release();
}

void GraphComponentRenderer::renderEdges()
{
    GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    _funcs->glDrawBuffers(2, drawBuffers);

    _shared->_edgesShader.bind();
    setShaderADSParameters(_shared->_edgesShader);

    _edgePositionBuffer.bind();
    _edgeVisualBuffer.bind();

    _shared->_edgesShader.setUniformValue("viewMatrix", _modelViewMatrix);
    _shared->_edgesShader.setUniformValue("projectionMatrix", _projectionMatrix);

    // Draw the edges
    _cylinder.vertexArrayObject()->bind();
    _funcs->glDrawElementsInstanced(GL_TRIANGLES, _cylinder.indexCount(),
                                    GL_UNSIGNED_INT, 0, _numEdgesInPositionData);
    _cylinder.vertexArrayObject()->release();

    _edgeVisualBuffer.release();
    _edgePositionBuffer.release();
    _shared->_edgesShader.release();
}

void GraphComponentRenderer::renderDebugLines()
{
    std::unique_lock<std::mutex> lock(_debugLinesMutex);

    _funcs->glDrawBuffer(GL_COLOR_ATTACHMENT0);

    _debugLinesDataBuffer.bind();
    _debugLinesDataBuffer.allocate(_debugLinesData.data(), static_cast<int>(_debugLinesData.size()) * sizeof(GLfloat));

    _shared->_debugLinesShader.bind();

    // Calculate needed matrices
    _shared->_debugLinesShader.setUniformValue("modelViewMatrix", _modelViewMatrix);
    _shared->_debugLinesShader.setUniformValue("projectionMatrix", _projectionMatrix);

    _debugLinesDataVAO.bind();
    _funcs->glDrawArrays(GL_LINES, 0, static_cast<int>(_debugLines.size()) * 2);
    _debugLinesDataVAO.release();
    _shared->_debugLinesShader.release();
    _debugLinesDataBuffer.release();

    clearDebugLines();
}

void GraphComponentRenderer::render2D()
{
    _funcs->glDisable(GL_DEPTH_TEST);

    QMatrix4x4 m;
    m.ortho(0.0f, _width, 0.0f, _height, -1.0f, 1.0f);

    if(!_selectionRect.isNull())
    {
        const QColor color(Qt::GlobalColor::white);

        QRect r;
        r.setLeft(_selectionRect.left());
        r.setRight(_selectionRect.right());
        r.setTop(_height - _selectionRect.top());
        r.setBottom(_height - _selectionRect.bottom());

        std::vector<GLfloat> data;

        data.push_back(r.left()); data.push_back(r.bottom());
        data.push_back(color.redF()); data.push_back(color.blueF()); data.push_back(color.greenF());
        data.push_back(r.right()); data.push_back(r.bottom());
        data.push_back(color.redF()); data.push_back(color.blueF()); data.push_back(color.greenF());
        data.push_back(r.right()); data.push_back(r.top());
        data.push_back(color.redF()); data.push_back(color.blueF()); data.push_back(color.greenF());

        data.push_back(r.right()); data.push_back(r.top());
        data.push_back(color.redF()); data.push_back(color.blueF()); data.push_back(color.greenF());
        data.push_back(r.left());  data.push_back(r.top());
        data.push_back(color.redF()); data.push_back(color.blueF()); data.push_back(color.greenF());
        data.push_back(r.left());  data.push_back(r.bottom());
        data.push_back(color.redF()); data.push_back(color.blueF()); data.push_back(color.greenF());

        _funcs->glDrawBuffer(GL_COLOR_ATTACHMENT1);

        _selectionMarkerDataBuffer.bind();
        _selectionMarkerDataBuffer.allocate(data.data(), static_cast<int>(data.size()) * sizeof(GLfloat));

        _shared->_selectionMarkerShader.bind();
        _shared->_selectionMarkerShader.setUniformValue("projectionMatrix", m);

        _selectionMarkerDataVAO.bind();
        _funcs->glDrawArrays(GL_TRIANGLES, 0, 6);
        _selectionMarkerDataVAO.release();

        _shared->_selectionMarkerShader.release();
        _selectionMarkerDataBuffer.release();
    }

    _funcs->glEnable(GL_DEPTH_TEST);
}

void GraphComponentRenderer::addDebugBoundingBox(const BoundingBox3D& boundingBox, const QColor color)
{
    const QVector3D& min = boundingBox.min();
    const QVector3D& max = boundingBox.max();

    const QVector3D _0 = QVector3D(min.x(), min.y(), min.z());
    const QVector3D _1 = QVector3D(max.x(), min.y(), min.z());
    const QVector3D _2 = QVector3D(min.x(), max.y(), min.z());
    const QVector3D _3 = QVector3D(max.x(), max.y(), min.z());
    const QVector3D _4 = QVector3D(min.x(), min.y(), max.z());
    const QVector3D _5 = QVector3D(max.x(), min.y(), max.z());
    const QVector3D _6 = QVector3D(min.x(), max.y(), max.z());
    const QVector3D _7 = QVector3D(max.x(), max.y(), max.z());

    addDebugLine(_0, _1, color);
    addDebugLine(_1, _3, color);
    addDebugLine(_3, _2, color);
    addDebugLine(_2, _0, color);

    addDebugLine(_4, _5, color);
    addDebugLine(_5, _7, color);
    addDebugLine(_7, _6, color);
    addDebugLine(_6, _4, color);

    addDebugLine(_0, _4, color);
    addDebugLine(_1, _5, color);
    addDebugLine(_3, _7, color);
    addDebugLine(_2, _6, color);
}

void GraphComponentRenderer::submitDebugLines()
{
    std::unique_lock<std::mutex> lock(_debugLinesMutex);

    _debugLinesData.resize(_debugLines.size() * 12);

    int i = 0;
    for(const DebugLine debugLine : _debugLines)
    {
        _debugLinesData[i++] = debugLine._start.x();
        _debugLinesData[i++] = debugLine._start.y();
        _debugLinesData[i++] = debugLine._start.z();
        _debugLinesData[i++] = debugLine._color.redF();
        _debugLinesData[i++] = debugLine._color.greenF();
        _debugLinesData[i++] = debugLine._color.blueF();
        _debugLinesData[i++] = debugLine._end.x();
        _debugLinesData[i++] = debugLine._end.y();
        _debugLinesData[i++] = debugLine._end.z();
        _debugLinesData[i++] = debugLine._color.redF();
        _debugLinesData[i++] = debugLine._color.greenF();
        _debugLinesData[i++] = debugLine._color.blueF();
    }
}

void GraphComponentRenderer::render(int x, int y, int width, int height, float alpha)
{
    if(!_initialised)
        return;

    if(!_FBOcomplete)
    {
        qWarning() << "Attempting to render component" <<
                      _componentId << "without a complete FBO";
        return;
    }

    if(width <= 0)
        width = _width;

    if(height <= 0)
        height = _height;

    _funcs->glEnable(GL_DEPTH_TEST);
    _funcs->glEnable(GL_CULL_FACE);
    _funcs->glDisable(GL_BLEND);

    int viewportWidth = std::min(width, _width);
    int viewportHeight = std::min(height, _height);
    _funcs->glViewport(0, _height - viewportHeight, viewportWidth, viewportHeight);
    _funcs->glBindFramebuffer(GL_FRAMEBUFFER, _visualFBO);

    // Color buffer
    _funcs->glDrawBuffer(GL_COLOR_ATTACHMENT0);
    _funcs->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    _funcs->glClear(GL_COLOR_BUFFER_BIT);

    // Selection buffer
    _funcs->glDrawBuffer(GL_COLOR_ATTACHMENT1);
    _funcs->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    _funcs->glClear(GL_COLOR_BUFFER_BIT);

    GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    _funcs->glDrawBuffers(2, drawBuffers);
    _funcs->glClear(GL_DEPTH_BUFFER_BIT);

    renderNodes();
    renderEdges();
    render2D();

    renderDebugLines();

    _funcs->glViewport(0, 0, _viewportWidth, _viewportHeight);
    _funcs->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    _funcs->glDisable(GL_DEPTH_TEST);

    QMatrix4x4 m;
    m.ortho(0, _viewportWidth, 0, _viewportHeight, -1.0f, 1.0f);

    int quadWidth = std::max(width, _width);
    int quadHeight = std::max(height, _height);
    QRect rect;
    rect.setLeft(x);
    rect.setRight(rect.left() + quadWidth);
    rect.setTop(_viewportHeight - y);
    rect.setBottom(rect.top() - quadHeight);

    GLfloat l = static_cast<GLfloat>(rect.left());
    GLfloat r = static_cast<GLfloat>(rect.right());
    GLfloat b = static_cast<GLfloat>(rect.bottom());
    GLfloat t = static_cast<GLfloat>(rect.top());
    GLfloat w = static_cast<GLfloat>(_width);
    GLfloat h = static_cast<GLfloat>(_height);
    GLfloat data[] =
    {
        l, b, 0, 0, 1.0f, 1.0f, 1.0f, alpha,
        r, b, w, 0, 1.0f, 1.0f, 1.0f, alpha,
        r, t, w, h, 1.0f, 1.0f, 1.0f, alpha,

        r, t, w, h, 1.0f, 1.0f, 1.0f, alpha,
        l, t, 0, h, 1.0f, 1.0f, 1.0f, alpha,
        l, b, 0, 0, 1.0f, 1.0f, 1.0f, alpha,
    };

    _screenQuadDataBuffer.bind();
    _screenQuadDataBuffer.allocate(data, static_cast<int>(sizeof(data)));

    _screenQuadVAO.bind();
    _funcs->glActiveTexture(GL_TEXTURE0);
    _funcs->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _funcs->glEnable(GL_BLEND);

    // Color texture
    _funcs->glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _colorTexture);

    _shared->_screenShader.bind();
    _shared->_screenShader.setUniformValue("projectionMatrix", m);
    _funcs->glDrawArrays(GL_TRIANGLES, 0, 6);
    _shared->_screenShader.release();

    // Selection texture
    _funcs->glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _selectionTexture);

    _shared->_selectionShader.bind();
    _shared->_selectionShader.setUniformValue("projectionMatrix", m);
    _funcs->glDrawArrays(GL_TRIANGLES, 0, 6);
    _shared->_selectionShader.release();

    _screenQuadVAO.release();
    _screenQuadDataBuffer.release();

    _funcs->glEnable(GL_DEPTH_TEST);
    _funcs->glDisable(GL_BLEND);
}

void GraphComponentRenderer::resize(int width, int height)
{
    if(_initialised && width > 0 && height > 0)
    {
        _width = width;
        _height = height;

        _FBOcomplete = prepareRenderBuffers();

        _aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        _fovy = 60.0f;
        _fovx = _fovy * _aspectRatio;

        if(_graphModel)
            setupCamera(_viewData._camera, _fovy, _aspectRatio);
    }
    else
    {
        qWarning() << "GraphComponentRenderer::resize(" << width << "," << height <<
                    ") failed _initialised:" << _initialised;
    }
}

void GraphComponentRenderer::resizeViewport(int width, int height)
{
    _viewportWidth = width;
    _viewportHeight = height;
}

const float MINIMUM_ZOOM_DISTANCE = 2.5f;

void GraphComponentRenderer::zoom(float direction)
{
    if(direction == 0.0f || !_graphWidget->transition().finished())
        return;

    // Don't allow zooming out if autozooming
    if(direction < 0.0f && _viewData._autoZooming)
        return;

    float size = 0.0f;

    _viewData._autoZooming = false;

    if(!_viewData._focusNodeId.isNull())
        size = _graphModel->nodeVisuals().at(_viewData._focusNodeId)._size;

    const float INTERSECTION_AVOIDANCE_OFFSET = 1.0f;
    const float ZOOM_STEP_FRACTION = 0.2f;
    float delta = (_targetZoomDistance - size - INTERSECTION_AVOIDANCE_OFFSET) * ZOOM_STEP_FRACTION;

    _targetZoomDistance -= delta * direction;
    _targetZoomDistance = std::max(_targetZoomDistance, MINIMUM_ZOOM_DISTANCE);

    if(_targetZoomDistance > _entireComponentZoomDistance)
    {
        _targetZoomDistance = _entireComponentZoomDistance;

        // If we zoom out all the way then use autozoom mode
        if(_viewData._focusNodeId.isNull())
            _viewData._autoZooming = true;
    }

    float startZoomDistance = _viewData._zoomDistance;

    if(visible())
    {
        if(_zoomTransition.finished())
        {
            _graphWidget->rendererStartedTransition();
        }
        _zoomTransition.start(0.1f, Transition::Type::Linear,
            [=](float f)
            {
                _viewData._zoomDistance = startZoomDistance + ((_targetZoomDistance - startZoomDistance) * f);
            },
            [this]
            {
                _graphWidget->rendererFinishedTransition();
            });
    }
    else
        _viewData._zoomDistance = _targetZoomDistance;
}

void GraphComponentRenderer::zoomToDistance(float distance)
{
    distance = std::max(distance, MINIMUM_ZOOM_DISTANCE);
    distance = std::min(distance, _entireComponentZoomDistance);
    _viewData._zoomDistance = _targetZoomDistance = distance;
}

void GraphComponentRenderer::centreNodeInViewport(NodeId nodeId, float cameraDistance)
{
    if(nodeId.isNull())
        return;

    centrePositionInViewport(_graphModel->nodePositions().getScaledAndSmoothed(nodeId),
                             cameraDistance);
}

void GraphComponentRenderer::centrePositionInViewport(const QVector3D& viewTarget, float cameraDistance)
{
    QVector3D startPosition = _viewData._camera.position();
    QVector3D startViewTarget = _viewData._camera.viewTarget();
    QVector3D position;

    if(cameraDistance < 0.0f)
    {
        Plane translationPlane(viewTarget, _viewData._camera.viewVector().normalized());

        if(translationPlane.sideForPoint(_viewData._camera.position()) == Plane::Side::Back)
        {
            // We're behind the translation plane, so move along it
            QVector3D cameraPlaneIntersection = translationPlane.rayIntersection(
                        Ray(_viewData._camera.position(), _viewData._camera.viewVector().normalized()));
            QVector3D translation = viewTarget - cameraPlaneIntersection;

            position = _viewData._camera.position() + translation;
        }
        else
        {
            // We're in front of the translation plane, so move directly to the target
            position = viewTarget + (startPosition - startViewTarget);
        }

        float distanceToTarget = (viewTarget - position).length();
        zoomToDistance(distanceToTarget);
    }
    else
    {
        // Given a specific camera distance
        position = viewTarget - (_viewData._camera.viewVector().normalized() * cameraDistance);
    }

    // Enforce minimum camera distance
    if(position.distanceToPoint(viewTarget) < MINIMUM_ZOOM_DISTANCE)
        position = viewTarget - (_viewData._camera.viewVector().normalized() * MINIMUM_ZOOM_DISTANCE);

    // Enforce maximum camera distance
    if(position.distanceToPoint(viewTarget) > _entireComponentZoomDistance)
        position = viewTarget - (_viewData._camera.viewVector().normalized() * _entireComponentZoomDistance);

    if(_graphWidget->transition().finished())
    {
        _viewData._camera.setPosition(position);
        _viewData._camera.setViewTarget(viewTarget);
    }
    else
    {
        _viewData._transitionStartPosition = startPosition;
        _viewData._transitionEndPosition = position;
        _viewData._transitionStartViewTarget = startViewTarget;
        _viewData._transitionEndViewTarget = viewTarget;
    }
}

void GraphComponentRenderer::moveFocusToNode(NodeId nodeId)
{
    if(_componentId.isNull())
        return;

    _viewData._focusNodeId = nodeId;
    _viewData._autoZooming = false;
    updateEntireComponentZoomDistance();

    centreNodeInViewport(nodeId, -1.0f);
}

void GraphComponentRenderer::resetView()
{
    if(_componentId.isNull())
        return;

    _viewData._autoZooming = true;

    moveFocusToCentreOfComponent();
}

void GraphComponentRenderer::moveFocusToCentreOfComponent()
{
    if(_componentId.isNull())
        return;

    _viewData._focusNodeId.setToNull();
    updateEntireComponentZoomDistance();

    if(_viewData._autoZooming)
        zoomToDistance(_entireComponentZoomDistance);
    else
        _viewData._zoomDistance = -1.0f;

    centrePositionInViewport(_viewData._focusPosition, _viewData._zoomDistance);
}

void GraphComponentRenderer::moveFocusToNodeClosestCameraVector()
{
    if(_componentId.isNull())
        return;

    Collision collision(*_graphModel, _componentId);
    //FIXME closestNodeToCylinder/Cone?
    NodeId closestNodeId = collision.nodeClosestToLine(_viewData._camera.position(), _viewData._camera.viewVector().normalized());
    if(!closestNodeId.isNull())
        moveFocusToNode(closestNodeId);
}

void GraphComponentRenderer::moveFocusToPositionContainingNodes(const QVector3D& position, std::vector<NodeId> nodeIds)
{
    if(_componentId.isNull())
        return;

    _viewData._focusNodeId.setToNull();
    _viewData._focusPosition = position;
    _entireComponentZoomDistance = zoomDistanceForNodeIds(position, nodeIds);
    zoomToDistance(_entireComponentZoomDistance);

    centrePositionInViewport(_viewData._focusPosition, _viewData._zoomDistance);
}

void GraphComponentRenderer::updateTransition(float f)
{
    _viewData._camera.setPosition(Utils::interpolate(_viewData._transitionStartPosition,
                                                     _viewData._transitionEndPosition, f));
    _viewData._camera.setViewTarget(Utils::interpolate(_viewData._transitionStartViewTarget,
                                                       _viewData._transitionEndViewTarget, f));
}

NodeId GraphComponentRenderer::focusNodeId()
{
    return _viewData._focusNodeId;
}

QVector3D GraphComponentRenderer::focusPosition()
{
    if(_viewData._focusNodeId.isNull())
        return _viewData._focusPosition;
    else
        return _graphModel->nodePositions().getScaledAndSmoothed(_viewData._focusNodeId);
}

bool GraphComponentRenderer::trackingCentreOfComponent()
{
    return _viewData._focusNodeId.isNull();
}

bool GraphComponentRenderer::autoZooming()
{
    return _viewData._autoZooming;
}

void GraphComponentRenderer::prepareVertexBuffers()
{
    // Populate the data buffer object
    _nodePositionBuffer.create();
    _nodePositionBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    _nodePositionBuffer.bind();
    _nodePositionBuffer.allocate(_nodePositionData.data(), static_cast<int>(_nodePositionData.size()) * sizeof(GLfloat));
    _nodePositionBuffer.release();

    _edgePositionBuffer.create();
    _edgePositionBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    _edgePositionBuffer.bind();
    _edgePositionBuffer.allocate(_edgePositionData.data(), static_cast<int>(_edgePositionData.size()) * sizeof(GLfloat));
    _edgePositionBuffer.release();

    _nodeVisualBuffer.create();
    _nodeVisualBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _nodeVisualBuffer.bind();
    _nodeVisualBuffer.allocate(_nodeVisualData.data(), static_cast<int>(_nodeVisualData.size()) * sizeof(GLfloat));
    _nodeVisualBuffer.release();

    _edgeVisualBuffer.create();
    _edgeVisualBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _edgeVisualBuffer.bind();
    _edgeVisualBuffer.allocate(_edgeVisualData.data(), static_cast<int>(_edgeVisualData.size()) * sizeof(GLfloat));
    _edgeVisualBuffer.release();

    _selectionMarkerDataBuffer.create();
    _selectionMarkerDataBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);

    _debugLinesDataBuffer.create();
    _debugLinesDataBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    _debugLinesDataBuffer.bind();
    _debugLinesDataBuffer.allocate(_debugLinesData.data(), static_cast<int>(_debugLinesData.size()) * sizeof(GLfloat));
    _debugLinesDataBuffer.release();
}

void GraphComponentRenderer::prepareNodeVAO()
{
    _sphere.vertexArrayObject()->bind();

    QOpenGLShaderProgramPtr shader = _sphere.material()->shader();
    shader->bind();
    _nodePositionBuffer.bind();
    shader->enableAttributeArray("point");
    shader->setAttributeBuffer("point", GL_FLOAT, 0, 3);

    _nodeVisualBuffer.bind();
    shader->enableAttributeArray("size");
    shader->enableAttributeArray("color");
    shader->enableAttributeArray("outlineColor");
    shader->setAttributeBuffer("size", GL_FLOAT, 0, 1, 7 * sizeof(GLfloat));
    shader->setAttributeBuffer("color", GL_FLOAT, 1 * sizeof(GLfloat), 3, 7 * sizeof(GLfloat));
    shader->setAttributeBuffer("outlineColor", GL_FLOAT, 4 * sizeof(GLfloat), 3, 7 * sizeof(GLfloat));

    _funcs->glVertexAttribDivisor(shader->attributeLocation("point"), 1);
    _funcs->glVertexAttribDivisor(shader->attributeLocation("size"), 1);
    _funcs->glVertexAttribDivisor(shader->attributeLocation("color"), 1);
    _funcs->glVertexAttribDivisor(shader->attributeLocation("outlineColor"), 1);

    _nodeVisualBuffer.release();
    _nodePositionBuffer.release();
    shader->release();
    _sphere.vertexArrayObject()->release();
}

void GraphComponentRenderer::prepareEdgeVAO()
{
    _cylinder.vertexArrayObject()->bind();

    QOpenGLShaderProgramPtr shader = _cylinder.material()->shader();
    shader->bind();
    _edgePositionBuffer.bind();
    shader->enableAttributeArray("source");
    shader->enableAttributeArray("target");
    shader->setAttributeBuffer("source", GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
    shader->setAttributeBuffer("target", GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

    _edgeVisualBuffer.bind();
    shader->enableAttributeArray("size");
    shader->enableAttributeArray("color");
    shader->enableAttributeArray("outlineColor");
    shader->setAttributeBuffer("size", GL_FLOAT, 0, 1, 7 * sizeof(GLfloat));
    shader->setAttributeBuffer("color", GL_FLOAT, 1 * sizeof(GLfloat), 3, 7 * sizeof(GLfloat));
    shader->setAttributeBuffer("outlineColor", GL_FLOAT, 4 * sizeof(GLfloat), 3, 7 * sizeof(GLfloat));

    _funcs->glVertexAttribDivisor(shader->attributeLocation("source"), 1);
    _funcs->glVertexAttribDivisor(shader->attributeLocation("target"), 1);
    _funcs->glVertexAttribDivisor(shader->attributeLocation("size"), 1);
    _funcs->glVertexAttribDivisor(shader->attributeLocation("color"), 1);
    _funcs->glVertexAttribDivisor(shader->attributeLocation("outlineColor"), 1);

    _edgeVisualBuffer.release();
    _edgePositionBuffer.release();
    shader->release();
    _cylinder.vertexArrayObject()->release();
}

void GraphComponentRenderer::prepareSelectionMarkerVAO()
{
    _selectionMarkerDataVAO.bind();
    _shared->_selectionMarkerShader.bind();
    _selectionMarkerDataBuffer.bind();

    _shared->_selectionMarkerShader.enableAttributeArray("position");
    _shared->_selectionMarkerShader.enableAttributeArray("color");
    _shared->_selectionMarkerShader.disableAttributeArray("texCoord");
    _shared->_selectionMarkerShader.setAttributeBuffer("position", GL_FLOAT, 0, 2, 5 * sizeof(GLfloat));
    _shared->_selectionMarkerShader.setAttributeBuffer("color", GL_FLOAT, 2 * sizeof(GLfloat), 3, 5 * sizeof(GLfloat));

    _selectionMarkerDataBuffer.release();
    _selectionMarkerDataVAO.release();
    _shared->_selectionMarkerShader.release();
}

void GraphComponentRenderer::prepareDebugLinesVAO()
{
    _debugLinesDataVAO.bind();
    _shared->_debugLinesShader.bind();
    _debugLinesDataBuffer.bind();

    _shared->_debugLinesShader.enableAttributeArray("position");
    _shared->_debugLinesShader.enableAttributeArray("color");
    _shared->_debugLinesShader.setAttributeBuffer("position", GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
    _shared->_debugLinesShader.setAttributeBuffer("color", GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

    _debugLinesDataBuffer.release();
    _debugLinesDataVAO.release();
    _shared->_debugLinesShader.release();
}

void GraphComponentRenderer::prepareQuad()
{
    if(!_screenQuadVAO.isCreated())
        _screenQuadVAO.create();

    _screenQuadVAO.bind();

    _screenQuadDataBuffer.create();
    _screenQuadDataBuffer.bind();
    _screenQuadDataBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);

    _shared->_screenShader.bind();
    _shared->_screenShader.enableAttributeArray("position");
    _shared->_screenShader.enableAttributeArray("texCoord");
    _shared->_screenShader.enableAttributeArray("color");
    _shared->_screenShader.setAttributeBuffer("position", GL_FLOAT, 0, 2, 8 * sizeof(GLfloat));
    _shared->_screenShader.setAttributeBuffer("texCoord", GL_FLOAT, 2 * sizeof(GLfloat), 2, 8 * sizeof(GLfloat)); //FIXME GL_INT?
    _shared->_screenShader.setAttributeBuffer("color", GL_FLOAT, 4 * sizeof(GLfloat), 4, 8 * sizeof(GLfloat));
    _shared->_screenShader.setUniformValue("frameBufferTexture", 0);
    _shared->_screenShader.release();

    _shared->_selectionShader.bind();
    _shared->_selectionShader.enableAttributeArray("position");
    _shared->_selectionShader.enableAttributeArray("texCoord");
    _shared->_selectionShader.enableAttributeArray("color");
    _shared->_selectionShader.setAttributeBuffer("position", GL_FLOAT, 0, 2, 8 * sizeof(GLfloat));
    _shared->_selectionShader.setAttributeBuffer("texCoord", GL_FLOAT, 2 * sizeof(GLfloat), 2, 8 * sizeof(GLfloat)); //FIXME GL_INT?
    _shared->_selectionShader.setAttributeBuffer("color", GL_FLOAT, 4 * sizeof(GLfloat), 4, 8 * sizeof(GLfloat));
    _shared->_selectionShader.setUniformValue("frameBufferTexture", 0);
    _shared->_selectionShader.release();

    _screenQuadDataBuffer.release();
    _screenQuadVAO.release();
}

bool GraphComponentRenderer::prepareRenderBuffers()
{
    bool valid;

    // Color texture
    if(_colorTexture == 0)
        _funcs->glGenTextures(1, &_colorTexture);
    _funcs->glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _colorTexture);
    _funcs->glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, multisamples, GL_RGBA, _width, _height, GL_FALSE);
    _funcs->glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAX_LEVEL, 0);
    _funcs->glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

    // Selection texture
    if(_selectionTexture == 0)
        _funcs->glGenTextures(1, &_selectionTexture);
    _funcs->glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _selectionTexture);
    _funcs->glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, multisamples, GL_RGBA, _width, _height, GL_FALSE);
    _funcs->glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAX_LEVEL, 0);
    _funcs->glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

    // Depth texture
    if(_depthTexture == 0)
        _funcs->glGenTextures(1, &_depthTexture);
    _funcs->glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _depthTexture);
    _funcs->glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, multisamples, GL_DEPTH_COMPONENT, _width, _height, GL_FALSE);
    _funcs->glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAX_LEVEL, 0);
    _funcs->glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

    // Visual FBO
    if(_visualFBO == 0)
        _funcs->glGenFramebuffers(1, &_visualFBO);
    _funcs->glBindFramebuffer(GL_FRAMEBUFFER, _visualFBO);
    _funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, _colorTexture, 0);
    _funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D_MULTISAMPLE, _selectionTexture, 0);
    _funcs->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, _depthTexture, 0);

    GLenum status = _funcs->glCheckFramebufferStatus(GL_FRAMEBUFFER);
    valid = (status == GL_FRAMEBUFFER_COMPLETE);

    _funcs->glBindFramebuffer(GL_FRAMEBUFFER, 0);

    Q_ASSERT(valid);
    return valid;
}
