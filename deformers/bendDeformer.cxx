#include "bendDeformer.h"
#include "clockObject.h"

BendDeformer::BendDeformer(NodePath& nodePath, Axis axis) : Deformer(nodePath, axis) {
    options.func_map = {
        {"Bend", { &_bend, {-30, 30} } },
    };
}

void BendDeformer::update_vertex(LVecBase3f& vertex, LVecBase3f& tangent, LVecBase3f& binormal, double time) {
    // XXX: Barr has a different formula for this.
    // It contends that the variable being subtracted by 1/k is the same
    // as one of the axis it is deforming.

    double theta = _bend * (vertex[_minor_axis_a]);
    double inverse_bend = 1.0 / _bend;
    double main_zero = vertex[axis];
    vertex[axis] = -sin(theta) * (main_zero - (inverse_bend)) + vertex[axis];
    vertex[_minor_axis_a] = cos(theta) * (main_zero - inverse_bend) + inverse_bend;
}

