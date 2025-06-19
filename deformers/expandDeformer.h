#pragma once
#include "deformer.h"

class ExpandDeformer : public Deformer {
PUBLISHED:
    ExpandDeformer(NodePath& nodePath = NodePath(), Axis axis = Axis::X);

public:
    virtual void update_vertex(LVecBase3f& vertex, LVecBase3f& normal, double time);

private:
    float _scale = 1.0;
};

