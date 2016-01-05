#include "graphcomponentscene.h"
#include "graphrenderer.h"

#include "graphcomponentrenderer.h"

#include "../graph/graphmodel.h"

#include "../ui/graphquickitem.h"

GraphComponentScene::GraphComponentScene(GraphRenderer* graphRenderer) :
    Scene(graphRenderer),
    _graphRenderer(graphRenderer)
{
    connect(&_graphRenderer->graphModel()->graph(), &Graph::componentSplit, this, &GraphComponentScene::onComponentSplit, Qt::DirectConnection);
    connect(&_graphRenderer->graphModel()->graph(), &Graph::componentsWillMerge, this, &GraphComponentScene::onComponentsWillMerge, Qt::DirectConnection);
    connect(&_graphRenderer->graphModel()->graph(), &Graph::componentAdded, this, &GraphComponentScene::onComponentAdded, Qt::DirectConnection);
    connect(&_graphRenderer->graphModel()->graph(), &Graph::componentWillBeRemoved, this, &GraphComponentScene::onComponentWillBeRemoved, Qt::DirectConnection);
    connect(&_graphRenderer->graphModel()->graph(), &Graph::graphWillChange, this, &GraphComponentScene::onGraphWillChange, Qt::DirectConnection);
    connect(&_graphRenderer->graphModel()->graph(), &Graph::graphChanged, this, &GraphComponentScene::onGraphChanged, Qt::DirectConnection);
    connect(&_graphRenderer->graphModel()->graph(), &Graph::nodeWillBeRemoved, this, &GraphComponentScene::onNodeWillBeRemoved, Qt::DirectConnection);

    _defaultComponentId = _graphRenderer->graphModel()->graph().componentIdOfLargestComponent();
}

void GraphComponentScene::update(float t)
{
    if(componentRenderer() != nullptr)
    {
        componentRenderer()->setDimensions(QRect(0, 0, _width, _height));
        componentRenderer()->setAlpha(1.0f);
        componentRenderer()->update(t);
    }
}

void GraphComponentScene::setViewportSize(int width, int height)
{
    _width = width;
    _height = height;

    if(componentRenderer() != nullptr)
    {
        componentRenderer()->setDimensions(QRect(0, 0, width, height));
        componentRenderer()->setViewportSize(width, height);
    }
}

bool GraphComponentScene::transitionActive() const
{
    if(componentRenderer() != nullptr)
        return componentRenderer()->transitionActive();

    return false;
}

void GraphComponentScene::onShow()
{
    _graphRenderer->executeOnRendererThread([this]
    {
        if(visible())
        {
            for(GraphComponentRenderer* componentRenderer : _graphRenderer->componentRenderers())
                componentRenderer->setVisible(componentRenderer->componentId() == _componentId);
        }
    }, "GraphComponentScene::onShow (setVisible)");
}

void GraphComponentScene::setComponentId(ComponentId componentId)
{
    if(componentId.isNull())
        _componentId = _defaultComponentId;
    else
        _componentId = componentId;

    onShow();
}

void GraphComponentScene::saveViewData()
{
    if(componentRenderer() != nullptr)
        componentRenderer()->saveViewData();
}

bool GraphComponentScene::savedViewIsReset() const
{
    if(componentRenderer() == nullptr)
        return true;

    return componentRenderer()->savedViewIsReset();
}

void GraphComponentScene::restoreViewData()
{
    if(componentRenderer() != nullptr)
        componentRenderer()->restoreViewData();
}

void GraphComponentScene::resetView()
{
    if(componentRenderer() != nullptr)
        componentRenderer()->resetView();
}

bool GraphComponentScene::viewIsReset() const
{
    if(componentRenderer() == nullptr)
        return true;

    return componentRenderer()->viewIsReset();
}

GraphComponentRenderer* GraphComponentScene::componentRenderer() const
{
    return _graphRenderer->componentRendererForId(_componentId);
}

void GraphComponentScene::startTransition(float duration, Transition::Type transitionType,
                                          std::function<void()> finishedFunction)
{
    if(!_graphRenderer->transition().active())
        _graphRenderer->rendererStartedTransition();

    _graphRenderer->transition().start(duration, transitionType,
    [this](float f)
    {
        componentRenderer()->updateTransition(f);
    },
    [this]
    {
        _graphRenderer->rendererFinishedTransition();
    },
    finishedFunction);
}

void GraphComponentScene::onComponentSplit(const Graph* graph, const ComponentSplitSet& componentSplitSet)
{
    if(!visible())
        return;

    auto oldComponentId = componentSplitSet.oldComponentId();
    if(oldComponentId == _componentId)
    {
        // Both of these things still exist after this returns
        auto largestSplitter = graph->componentIdOfLargestComponent(componentSplitSet.splitters());
        auto oldGraphComponentRenderer = _graphRenderer->componentRendererForId(oldComponentId);

        _graphRenderer->executeOnRendererThread([this, largestSplitter, oldGraphComponentRenderer]
        {
            auto& graph = _graphRenderer->graphModel()->graph();

            ComponentId newComponentId;

            if(oldGraphComponentRenderer->trackingCentreOfComponent())
                newComponentId = largestSplitter;
            else
                newComponentId = graph.componentIdOfNode(oldGraphComponentRenderer->focusNodeId());

            Q_ASSERT(!newComponentId.isNull());

            auto newGraphComponentRenderer = _graphRenderer->componentRendererForId(newComponentId);

            newGraphComponentRenderer->cloneViewDataFrom(*oldGraphComponentRenderer);
            setComponentId(newComponentId);
        }, "GraphComponentScene::onComponentSplit (clone camera data, set component ID)");
    }
}

void GraphComponentScene::onComponentsWillMerge(const Graph*, const ComponentMergeSet& componentMergeSet)
{
    if(!visible())
        return;

    for(auto merger : componentMergeSet.mergers())
    {
        if(merger == _componentId)
        {
            auto newComponentId = componentMergeSet.newComponentId();
            auto newGraphComponentRenderer = _graphRenderer->componentRendererForId(newComponentId);
            auto oldGraphComponentRenderer = _graphRenderer->componentRendererForId(_componentId);

            _graphRenderer->executeOnRendererThread([this, newComponentId,
                                                    newGraphComponentRenderer,
                                                    oldGraphComponentRenderer]
            {
                // This occurs before GraphComponentRenderer::cleanup is called on oldGraphComponentRenderer
                newGraphComponentRenderer->cloneViewDataFrom(*oldGraphComponentRenderer);
                setComponentId(newComponentId);
            }, "GraphComponentScene::onComponentsWillMerge (clone camera data, set component ID)");
            break;
        }
    }
}

void GraphComponentScene::onComponentAdded(const Graph*, ComponentId componentId, bool)
{
    if(_componentId.isNull())
        setComponentId(componentId);
}

void GraphComponentScene::onComponentWillBeRemoved(const Graph*, ComponentId componentId, bool hasMerged)
{
    if(componentId == _componentId)
    {
        if(visible() && !hasMerged)
            _graphRenderer->switchToOverviewMode();

        _componentId.setToNull();
    }
}

void GraphComponentScene::onGraphWillChange(const Graph* graph)
{
    _numComponentsPriorToChange = graph->numComponents();
}

void GraphComponentScene::onGraphChanged(const Graph* graph)
{
    _graphRenderer->executeOnRendererThread([this, graph]
    {
        _defaultComponentId = graph->componentIdOfLargestComponent();

        if(visible())
        {
            setViewportSize(_width, _height);

            // Graph changes may significantly alter the centre; ease the transition
            if(componentRenderer() != nullptr && componentRenderer()->trackingCentreOfComponent())
            {
                startTransition(0.3f, Transition::Type::EaseInEaseOut,
                [this, graph]
                {
                    // If graph change has resulted in multiple components, switch
                    // to overview mode once the transition had completed
                    if(_numComponentsPriorToChange == 1 && graph->numComponents() > 1)
                        _graphRenderer->switchToOverviewMode();
                });
                componentRenderer()->moveFocusToCentreOfComponent();
            }
        }
    }, "GraphComponentScene::onGraphChanged (setSize/moveFocusToCentreOfComponent)");
}

void GraphComponentScene::onNodeWillBeRemoved(const Graph*, const Node* node)
{
    if(visible() && componentRenderer()->focusNodeId() == node->id())
    {
        _graphRenderer->executeOnRendererThread([this]
        {
            startTransition();
            componentRenderer()->moveFocusToCentreOfComponent();
        }, "GraphWidget::onNodeWillBeRemoved");
    }
}
