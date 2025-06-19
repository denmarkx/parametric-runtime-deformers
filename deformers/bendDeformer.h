#ifndef BEND_DEFORMER_H
#define BEND_DEFORMER_H
#include "deformer.h"

class BendDeformer : public Deformer {
public:
    BendDeformer(NodePath& nodePath, Axis axis=Axis::X);
    virtual void update_vertex(LVecBase3f& vertex, double time);
    inline virtual void set_axis(Axis new_axis);

private:
    float _bend = 1.0;
    float _center = 0.0;
    float _top = 1.0;
    float _bottom = 0.0;
};

#endif