#ifndef SINE_DEFORMER_H
#define SINE_DEFORMER_H
#include "deformer.h"

enum WaveForm {
    SINE,
    SQUARE,
};

class SineDeformer : public Deformer {
public:
    SineDeformer(NodePath& nodePath, Axis axis = Axis::X, WaveForm wave_form = WaveForm::SINE);
    virtual void update_vertex(LVecBase3f& vertex, LVecBase3f& normal, double time);
    WaveForm _wave_form;
    void set_wave_form(WaveForm wave_form);
    WaveForm get_wave_form(WaveForm wave_form);

private:
    inline int sgn(double x);

    float _frequency = 1.0;
    float _speed = 1.0;
    float _amplitude = 1.0;
};

#endif