#include "sineDeformer.h"
#include "clockObject.h"

SineDeformer::SineDeformer(NodePath& nodePath, Axis axis) : Deformer(nodePath, axis) {
    options.func_map = { 
        {"Amplitude", { &_amplitude, {0.0, 5.0} } },
        {"Frequency", { &_frequency, {0.0, 5.0} } },
        {"Time", { &_speed, {1.0, 10.0} } },
    };
}

void SineDeformer::update_vertex(LVecBase3f& vertex, LVecBase3f& normal, double time) {
    vertex[axis] += sin(_speed+vertex[1] * _frequency) * _amplitude;
}
