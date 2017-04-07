#ifndef ELEMENTTYPE_H
#define ELEMENTTYPE_H

#include "utils/qmlenum.h"

DEFINE_QML_ENUM(Q_GADGET, ElementType,
                None        = 0x1,
                Node        = 0x2,
                Edge        = 0x4,
                Component   = 0x8,
                All = Node|Edge|Component);

QString elementTypeAsString(ElementType elementType);

#endif // ELEMENTTYPE_H
