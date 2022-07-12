#pragma once
#include "geo.h"

class shapeManager {
    public:
        virtual ~shapeManager () {}
        virtual void visitShapes (ShapeVisitor * visitor) = 0;
        virtual void visitHulledShapes (ShapeVisitor * visitor) = 0;
        virtual void addShape (Shape * shape) = 0;
};
