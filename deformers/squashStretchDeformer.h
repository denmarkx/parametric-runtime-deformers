#pragma once
#include "deformer.h"

class SquashStretchDeformer : public Deformer {
PUBLISHED:
    SquashStretchDeformer(NodePath& nodePath = NodePath(), Axis axis = Axis::X);

public:
    virtual void update_vertex(LVecBase3f& vertex, LVecBase3f& normal, double time);
    double lerp(double v0, double v1, double t);

private:
    inline double squash_equation() const;

private:
    float _scale = 1.0;
    float _expand = 1.0;
    float _low_bound = 1.5;
    float _high_bound = 3.3;
};
