#include "twistDeformer.h"

/*
* Circular twist deformation. Twists relative to the nodePath's center or
* an arbitrary point/NodePath provided by set_other.
*/
TwistDeformer::TwistDeformer(NodePath& nodePath, Axis axis) : Deformer(nodePath, axis) {
    options.func_map = {
        {"Twist", { &_twist, {-5.0, 5.0} } },
    };
}

/*
* Updates the vertices. The major axis is accounted into the twist angle. The 
* two manipulated vertex axes are both minor ones.
*/
void TwistDeformer::update_vertex(LVecBase3f& vertex, double time) {
    double theta = _twist * vertex[get_axis()];
    double x = vertex[_minor_axis_a] + get_center()[_minor_axis_a];
    double y = vertex[_minor_axis_b] + get_center()[_minor_axis_b];
    vertex[_minor_axis_a] = (x * cos(theta)) - y * sin(theta);
    vertex[_minor_axis_b] = (x * sin(theta)) + y * cos(theta);
}
