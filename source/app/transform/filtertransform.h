#ifndef FILTERTRANSFORM_H
#define FILTERTRANSFORM_H

#include "graphtransform.h"
#include "graph/graph.h"
#include "attributes/attribute.h"

#include <vector>

class FilterTransform : public GraphTransform
{
public:
    explicit FilterTransform(ElementType elementType,
                             const NameAttributeMap& attributes,
                             const GraphTransformConfig& graphTransformConfig,
                             bool invert) :
        _elementType(elementType),
        _attributes(&attributes),
        _graphTransformConfig(graphTransformConfig),
        _invert(invert)
    {}

    bool apply(TransformedGraph &target) const;

private:
    ElementType _elementType;
    const NameAttributeMap* _attributes;
    GraphTransformConfig _graphTransformConfig;
    bool _invert = false;
};

class FilterTransformFactory : public GraphTransformFactory
{
private:
    ElementType _elementType = ElementType::None;
    bool _invert = false;

public:
    FilterTransformFactory(GraphModel* graphModel, ElementType elementType, bool invert) :
        GraphTransformFactory(graphModel),
        _elementType(elementType), _invert(invert)
    {}

    QString description() const
    {
        return QObject::tr("%1 all the %2s which match the specified condition.")
                .arg(_invert ? QObject::tr("Keep") : QObject::tr("Remove"))
                .arg(elementTypeAsString(_elementType).toLower());
    }
    ElementType elementType() const { return _elementType; }
    TransformRequirements requirements() const { return TransformRequirements::Condition; }

    std::unique_ptr<GraphTransform> create(const GraphTransformConfig& graphTransformConfig) const;
};

#endif // FILTERTRANSFORM_H
