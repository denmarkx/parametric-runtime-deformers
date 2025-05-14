#ifndef TWIST_DEFORMER_H
#define TWIST_DEFORMER_H
#include "deformer.h"

class TwistDeformer : public Deformer {
public:
    TwistDeformer(NodePath& nodePath, Axis axis=Axis::X);
    virtual void update_vertex(LVecBase3f& vertex, LVecBase3f& tangent, LVecBase3f& binormal, double time);

private:
    float _twist = 1.0;
};

#endif