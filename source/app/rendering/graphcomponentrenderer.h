#ifndef GRAPHCOMPONENTRENDERER_H
#define GRAPHCOMPONENTRENDERER_H

#include "camera.h"
#include "transition.h"
#include "maths/boundingbox.h"

#include "shared/graph/igraph.h"
#include "shared/graph/grapharray.h"

#include <QMatrix4x4>
#include <QVector3D>
#include <QQuaternion>
#include <QColor>
#include <QRect>

#include <memory>
#include <vector>

class GraphRenderer;
class GraphModel;
class SelectionManager;
class Camera;
class Octree;

class GraphComponentRenderer
{
public:
    static const float MINIMUM_ZOOM_DISTANCE;
    static const float COMFORTABLE_ZOOM_RADIUS;

    GraphComponentRenderer() = default;

    void initialise(GraphModel* graphModel, ComponentId componentId,
                    SelectionManager* selectionManager,
                    GraphRenderer* graphRenderer);

    bool visible() const { return _initialised && _visible; }
    void setVisible(bool visible);

    void cleanup();
    void synchronise();
    void update(float t);
    void setViewportSize(int viewportWidth, int viewportHeight);
    void setDimensions(const QRectF& dimensions);

    bool transitionActive();

    int viewportWidth() const { return _viewportWidth; }
    int viewportHeight() const { return _viewportHeight; }

    int width() const { return _dimensions.width(); }
    int height() const { return _dimensions.height(); }

    float alpha() const { return _alpha; }
    void setAlpha(float alpha);

    QMatrix4x4 modelViewMatrix() const;
    QMatrix4x4 projectionMatrix() const;

    void moveFocusToNode(NodeId nodeId, float radius = -1.0f);
    void moveSavedFocusToNode(NodeId nodeId);
    void moveFocusToCentreOfComponent();
    void moveFocusToNodeClosestCameraVector();
    void moveFocusToNodes(const std::vector<NodeId>& nodeIds,
        const QQuaternion& rotation);

    ComponentId componentId() const { return _componentId; }
    const std::vector<NodeId>& nodeIds() const { return _nodeIds; }
    std::vector<const IEdge*> edges() const { return _edges; }

    NodeId focusNodeId() const;
    bool focusNodeIsVisible() const;
    QVector3D focusPosition() const;
    void enableFocusTracking() { _trackFocus = true; }
    void disableFocusTracking() { _trackFocus = false; }

    bool focusedOnNodeAtRadius(NodeId nodeId, float radius) const;

    bool trackingCentreOfComponent() const;

    void resetView();
    bool viewIsReset() const { return _viewData.isReset(); }

    Camera* camera() { return &_viewData._camera; }
    const Camera* camera() const { return &_viewData._camera; }
    void zoom(float delta, bool doTransition);
    void zoomToDistance(float distance);

    void cloneViewDataFrom(const GraphComponentRenderer& other);
    void saveViewData() { _savedViewData = _viewData; }
    bool savedViewIsReset() const { return _savedViewData.isReset(); }
    void restoreViewData();

    bool initialised() const { return _initialised; }

    void freeze();
    void thaw();

    bool componentIsValid() const { return !componentId().isNull() && !_frozen; }

    bool transitionRequired();
    void computeTransition();
    void updateTransition(float f);

    static float maxNodeDistanceFromPoint(const GraphModel& graphModel,
                                          const QVector3D& centre,
                                          const std::vector<NodeId>& nodeIds);

private:
    GraphRenderer* _graphRenderer = nullptr;

    bool _initialised = false;
    bool _visible = false;

    bool _frozen = false;
    bool _cleanupWhenThawed = false;
    bool _synchroniseWhenThawed = false;

    struct ViewData
    {
        bool isReset() const { return _focusNodeId.isNull() && _autoZooming; }

        Camera _camera;
        float _zoomDistance = 1.0f;
        bool _autoZooming = true;
        NodeId _focusNodeId;
        QVector3D _componentCentre;

        Camera _transitionStart;
        Camera _transitionEnd;

        float _orthoStartZoomDistance = -1.0f;
        float _orthoEndZoomDistance = -1.0f;
    };

    ViewData _viewData;
    ViewData _savedViewData;

    int _viewportWidth = 0;
    int _viewportHeight = 0;

    QRectF _dimensions;

    float _alpha = 1.0f;

    bool _trackFocus = true;
    float _targetZoomDistance = 0.0f;
    Transition _zoomTransition;
    bool _moveFocusToCentreOfComponentLater = false;

    ComponentId _componentId;
    std::vector<NodeId> _nodeIds;
    std::vector<const IEdge*> _edges;

    float _fovx = 0.0f;
    float _fovy = 0.0f;

    GraphModel* _graphModel = nullptr;
    SelectionManager* _selectionManager = nullptr;

    QMatrix4x4 subViewportMatrix() const;

    void centreNodeInViewport(NodeId nodeId, float zoomDistance = -1.0f);
    void centrePositionInViewport(const QVector3D& focus, float zoomDistance = -1.0f,
        // Odd constructor makes a null quaternion
        QQuaternion rotation = QQuaternion(QVector4D()));

    float _entireComponentZoomDistance = 0.0f;
    float zoomDistanceForRadius(float radius) const;
    float entireComponentZoomDistanceFor(NodeId nodeId,
        const std::vector<NodeId>* nodeIds = nullptr) const;

    void updateCentreAndZoomDistance(const std::vector<NodeId>* nodeIds = nullptr);
};

#endif // GRAPHCOMPONENTRENDERER_H
