#ifndef SINE_DEFORMER_H
#define SINE_DEFORMER_H
#include "deformer.h"

class SineDeformer : public Deformer {
PUBLISHED:
    enum WaveForm {
        SINE,
        SQUARE,
        TRIANGLE,
    };

    SineDeformer(NodePath& nodePath, Axis axis = Axis::X, WaveForm wave_form = WaveForm::SINE);
    inline void set_wave_form(WaveForm wave_form);
    inline WaveForm get_wave_form();

public:
    virtual void update_vertex(LVecBase3f& vertex, LVecBase3f& normals, double time);

private:
    inline int sgn(double x);

    WaveForm _wave_form;

    float _frequency = 1.0;
    float _speed = 1.0;
    float _amplitude = 1.0;
};

// Appeasing interrogate by moving set_wave_form/get_wave_form here:
#include "sineDeformer.I"

#endif
