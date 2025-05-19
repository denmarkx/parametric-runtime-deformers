#include "sineDeformer.h"

SineDeformer::SineDeformer(NodePath& nodePath, Axis axis, WaveForm wave_form): Deformer(nodePath, axis) {
    options.func_map = { 
        {"Amplitude", { &_amplitude, {0.0, 5.0} } },
        {"Frequency", { &_frequency, {0.0, 5.0} } },
        {"Time", { &_speed, {1.0, 10.0} } },
    };
    set_wave_form(wave_form);
}

void SineDeformer::update_vertex(LVecBase3f& vertex, LVecBase3f& normal, double time) {
    // Base:
    double wave = sin(_speed + vertex[1] * _frequency);

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

/*
* Returns -1, 0, or 1 depending on the sign of x.
* Equivalent to sgn(x) in math notation.
*
* { -1   x < 0
* { 0    x = 0
* { 1    x > 0
*/
inline int SineDeformer::sgn(double x) {
    return (0 < x) - (x < 0);
}

/*
* Sets the WaveForm of the deformer.
*/
inline void SineDeformer::set_wave_form(WaveForm wave_form) {
    _wave_form = wave_form;
}

/*
* Returns the current WaveForm.
*/
inline WaveForm SineDeformer::get_wave_form(WaveForm wave_form) {
    return _wave_form;
}
