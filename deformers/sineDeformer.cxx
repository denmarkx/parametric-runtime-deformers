#include "sineDeformer.h"
#include "clockObject.h"

SineDeformer::SineDeformer(NodePath& nodePath) : Deformer(nodePath) {
    options.func_map = { 
        {"Frequency", { &_frequency, {0.0, 1.0} } },
    };
}

void SineDeformer::update_vertex(LVecBase3f& vertex, double time) {
    vertex.add_x(sin(time + vertex[1] * 1) * 1);
}
