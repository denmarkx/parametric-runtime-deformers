#ifndef SINE_DEFORMER_H
#define SINE_DEFORMER_H
#include "deformer.h"

class SineDeformer : public Deformer {
public:
    SineDeformer(NodePath& nodePath);
    virtual void update_vertex(LVecBase3f& vertex, LVecBase3f& tangent, LVecBase3f& binormal, double time);

private:
    float _frequency = 1.0;
    float _speed = 1.0;
    float _amplitude = 1.0;
};

#endif