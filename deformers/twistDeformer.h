#ifndef TWIST_DEFORMER_H
#define TWIST_DEFORMER_H
#include "deformer.h"

class TwistDeformer : public Deformer {
PUBLISHED:
    TwistDeformer(NodePath& nodePath, Axis axis = Axis::X);

public:
    virtual void update_vertex(LVecBase3f& vertex, LVecBase3f& normals, double time);

private:
    float _twist = 1.0;
};

#endif