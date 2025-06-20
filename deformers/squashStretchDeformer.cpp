#include "squashStretchDeformer.h"

/*
* Squashes and stretches an object based on arbitrary scale.
*/
SquashStretchDeformer::SquashStretchDeformer(NodePath& nodePath, Axis axis) : Deformer(nodePath, axis) {
    options.func_map = {
        {"Scale", { &_scale, {0.00001, 10.0} } },
        {"Expand", { &_expand, {0.00001, 10.0} } },
    };
}

/*
* Vertex updating function. General formula is sqrt(n) for entire mesh.
*/
void SquashStretchDeformer::update_vertex(LVecBase3f& vertex, LVecBase3f& normal, double time) {
    vertex[get_minor_axis_a()] *= sqrt(_scale/(pow(_expand, -1.0)));
    vertex[get_minor_axis_b()] *= sqrt(_scale/(pow(_expand, -1.0)));
}
