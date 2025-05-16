#include "bendDeformer.h"
#include "clockObject.h"

BendDeformer::BendDeformer(NodePath& nodePath, Axis axis) : Deformer(nodePath, axis) {
    options.func_map = {
        {"Bend", { &_bend, {-2, 2} } },
        {"test", { &_test, {-10, 10} } },
    };
}

void BendDeformer::update_vertex(LVecBase3f& vertex, LVecBase3f& tangent, LVecBase3f& binormal, double time) {
    /*
    XXX: Barr has a different formula for this.
    * It stated that for each function within the first piecewise
    * function, you add the initial vertex value of that axis.
    * 
    * This led to a full and noticable offset on that axis
    * and stretching when you surpassed pi/2 or 3pi/2.
    * 
    * Additionally, it contends -sin(t) for the same axes...which inverts the mesh.
    */

    double theta = _bend * (vertex[_minor_axis_a]);
    double inverse_bend = 1.0 / _bend;
    double main_zero = vertex[axis];
    vertex[axis] = sin(theta) * (main_zero - (inverse_bend)); // + vertex[axis];
    vertex[_minor_axis_a] = cos(theta) * (main_zero - inverse_bend) + inverse_bend;
}

