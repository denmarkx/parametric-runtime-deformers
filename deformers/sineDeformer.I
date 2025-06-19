
/*
* Sets the WaveForm of the deformer.
*/
inline void SineDeformer::set_wave_form(WaveForm wave_form) {
    _wave_form = wave_form;
}

/*
* Returns the current WaveForm.
*/
inline SineDeformer::WaveForm SineDeformer::get_wave_form() {
    return _wave_form;
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