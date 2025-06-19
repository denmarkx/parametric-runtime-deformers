#ifndef BEND_DEFORMER_H
#define BEND_DEFORMER_H
#include "deformer.h"

class BendDeformer : public Deformer {
PUBLISHED:
    BendDeformer(NodePath& nodePath = NodePath(), Axis axis=Axis::X);
    inline virtual void set_axis(Axis new_axis);

public:
    virtual void update_vertex(LVecBase3f& vertex, LVecBase3f& normals, double time);

private:
    float _bend = 1.0;
    float _center = 0.0;
    float _top = 1.0;
    float _bottom = 0.0;
};

#endif