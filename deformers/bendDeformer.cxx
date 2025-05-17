#include "bendDeformer.h"
#include "clockObject.h"

BendDeformer::BendDeformer(NodePath& nodePath, Axis axis) : Deformer(nodePath, axis) {
    options.func_map = {
        {"Bend", { &_bend, {-2, 2} } },
        {"test", { &_test, {-3, 3} } },
    };
}

inline void BendDeformer::set_axis(Axis new_axis) {
    Deformer::set_axis(new_axis);

    LPoint3f _min, _max;
    get_node_path().calc_tight_bounds(_min, _max);
    _bottom = _min[new_axis]; _top = _max[new_axis];
}

void BendDeformer::update_vertex(LVecBase3f& vertex, LVecBase3f& tangent, LVecBase3f& binormal, double time) {
    /*
    * Converted into a visual parametric equation here:
    * https://www.desmos.com/3d/jh74yzrget 
    * 
    * y_min and y_max are equivalent to _bottom and _top, respectively.
    * 
    * Comment references to y is the same as the major axis.
    */

    // initial axis piecewise function:
    // { min : y <= min
    // { y   : min < y < max
    // { max : y >= max
    double n = vertex[axis];
    if (n <= _bottom) n = _bottom;
    if (n >= _top) n = _top;

    // Theta, C, and S:
    double theta = _bend * (n - _test);
    double c = cos(theta);
    double s = sin(theta);

    // Deformation Piecewise Function [Major Axis]:
    // { -s(z-1/k)+y0                : y_min <= y <= y_max
    // { ............ + c(y-_bottom) : y < y_min
    // { ............ + c(y-_top)    : y > y_max
    // ..where z is the minor axis.
    double m = vertex[_minor_axis_b];
    double N = (-s * (m - (1 / _bend))) + _test;

    if (n < _bottom) N += c * (n - _bottom);
    if (n > _top) N += c* (n - _top);

    // Deformation Piecewise Function [Minor Axis]:
    // { c(z-1/k)+1/k                 : y_min <= y <= y_max
    // { ............ + s(y-_bottom)  : y < y_min
    // { ............ + s(y-_top)     : y > y_max
    double M = (c * (m - (1 / _bend))) + 1 / _bend;

    if (n < _bottom) M += s * (n - _bottom);
    if (n > _top) M += s * (n - _top);

    vertex[axis] = N;
    vertex[_minor_axis_b] = M;
}

