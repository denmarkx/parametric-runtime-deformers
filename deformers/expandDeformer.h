#pragma once
#include "deformer.h"

class ExpandDeformer : public Deformer {
public:
    ExpandDeformer(NodePath& nodePath, Axis axis = Axis::X);
    virtual void update_vertex(LVecBase3f& vertex, LVecBase3f& normal, double time);

private:
    float _scale = 1.0;
};

