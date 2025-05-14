#include "twistDeformer.h"
#include "clockObject.h"

TwistDeformer::TwistDeformer(NodePath& nodePath) : Deformer(nodePath) {
    options.func_map = {
        {"Twist", { &_twist, {0.0, 20.0} } },
    };
}

void TwistDeformer::update_vertex(LVecBase3f& vertex, LVecBase3f& tangent, LVecBase3f& binormal, double time) {
    double theta = _twist * vertex[2]; // XXX: -2pi/2pi
    double x = vertex[0] + 5;
    double y = vertex[1] + 5;
    vertex[0] = (x * cos(theta)) - y * sin(theta);
    vertex[1] = (x * sin(theta)) + y * cos(theta);
}
