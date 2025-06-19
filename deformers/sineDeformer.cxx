#include "sineDeformer.h"

/*
* Periodic sine wave deformation. Available wave forms are SINE, SQUARE, and
* TRIANGLE. Square and Triangle waves are derived off of the base sine wave formula.
*/
SineDeformer::SineDeformer(NodePath& nodePath, Axis axis, WaveForm wave_form): Deformer(nodePath, axis) {
    options.func_map = { 
        {"Amplitude", { &_amplitude, {0.0, 5.0} } },
        {"Frequency", { &_frequency, {0.0, 5.0} } },
        {"Time", { &_speed, {1.0, 10.0} } },
    };
    set_wave_form(wave_form);
}

/*
* Updates the vertices. The second minor axis has no affect.
* Simple base formula is: vertex[major_axis] += sin(vertex[minor_axis_a])
*/
void SineDeformer::update_vertex(LVecBase3f& vertex, LVecBase3f& normals, double time) {
    vertex[axis] += sin(_speed+vertex[1] * _frequency) * _amplitude;
    // Base:
    double wave = sin(_speed + vertex[_minor_axis_a] * _frequency);

    // SIN / SQUARE:
    if (_wave_form == WaveForm::SINE || _wave_form == WaveForm::SQUARE) {
        wave *= _amplitude;
    }

    // SQUARE: (sgn(f(x)))
    if (_wave_form == WaveForm::SQUARE) {
        wave = sgn(wave);
    }

    // TRIANGLE: arcsin(f(x))
    if (_wave_form == WaveForm::TRIANGLE) {
        wave = asin(wave) * _amplitude;
    }


    vertex[axis] += wave;

}

