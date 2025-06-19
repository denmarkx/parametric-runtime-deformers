#include "twistDeformer.h"
#include "clockObject.h"

TwistDeformer::TwistDeformer(NodePath& nodePath, Axis axis) : Deformer(nodePath, axis) {
    options.func_map = {
        {"Twist", { &_twist, {-20.0, 20.0} } },
    };
}

void TwistDeformer::update_vertex(LVecBase3f& vertex, double time) {
    double theta = _twist * vertex[get_axis()];
    double x = vertex[_minor_axis_a] + get_center()[_minor_axis_a];
    double y = vertex[_minor_axis_b] + get_center()[_minor_axis_b];
    vertex[_minor_axis_a] = (x * cos(theta)) - y * sin(theta);
    vertex[_minor_axis_b] = (x * sin(theta)) + y * cos(theta);
}
