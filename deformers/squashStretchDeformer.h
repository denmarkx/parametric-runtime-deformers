#pragma once
#include "deformer.h"

class SquashStretchDeformer : public Deformer {
PUBLISHED:
    SquashStretchDeformer(NodePath& nodePath = NodePath(), Axis axis = Axis::X);

public:
    virtual void update_vertex(LVecBase3f& vertex, LVecBase3f& normal, double time);

private:
    float _scale = 1.0;
    float _expand = 1.0;
};

