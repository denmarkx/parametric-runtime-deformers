#include "sineDeformer.h"
#include "clockObject.h"

SineDeformer::SineDeformer(NodePath& nodePath) : Deformer(nodePath) {
    options.func_map = { 
        {"Frequency", { &_frequency, {0.0, 5.0} } },
    };
}

void SineDeformer::update_vertex(LVecBase3f& vertex, double time) {
    vertex.add_x(sin(time + vertex[1] * _frequency) * 1);
}
