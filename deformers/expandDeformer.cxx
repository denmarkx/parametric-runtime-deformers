#include "expandDeformer.h"

/*
* Inflates the given mesh on all axes. Any calls to
* set_axis are overriden by update_vertex.
*
* Requires vertex normals, otherwise you're better doing NodePath.set_scale.
* Because we're scaling based on the direction, your vertices will
* have to be connected or aligned for satisfying results.
*
*/
ExpandDeformer::ExpandDeformer(NodePath& nodePath, Axis axis) : Deformer(nodePath, axis) {
    options.func_map = { 
        {"Scale", { &_scale, {0, 10.0} } },
    };
}

void ExpandDeformer::update_vertex(LVecBase3f& vertex, LVecBase3f& normal, double time) {
    vertex[0] += normal[0] * _scale;
    vertex[1] += normal[1] * _scale;
    vertex[2] += normal[2] * _scale;
}
