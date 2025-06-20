#include "squashStretchDeformer.h"

/*
* Squashes and stretches an object based on arbitrary scale.
*/
SquashStretchDeformer::SquashStretchDeformer(NodePath& nodePath, Axis axis) : Deformer(nodePath, axis) {
    options.func_map = {
        {"Scale", { &_scale, {0.00001, 10.0} } },
        {"Expand", { &_expand, {0.00001, 10.0} } },
        {"Low Bound", { &_low_bound, {-5, 5.0} } },
        {"High Bound", { &_high_bound, {0, 5.0} } },
    };

    LPoint3f mip, map;
    nodePath.calc_tight_bounds(mip, map);
    std::cout << mip << "\n";
    std::cout << map << "\n";

}

/*
* Linear interpolation between [v0, v1] where t is [0, 1].
*/
double SquashStretchDeformer::lerp(double v0, double v1, double t) {
    return v0 + ((v1 - v0) * t);
}

/*
* Primary squash equation used: sqrt(scale/expand^-1.0)
*/
inline double SquashStretchDeformer::squash_equation() const {
    return sqrt(_scale / pow(_expand, -1.0));
}

/*
* Vertex updating function. General formula is sqrt(n) for entire mesh.
*/
void SquashStretchDeformer::update_vertex(LVecBase3f& vertex, LVecBase3f& normal, double time) {
    double minor_a = vertex[get_minor_axis_a()];
    double minor_b = vertex[get_minor_axis_b()];
    double major = vertex[get_axis()];
    double step = 0.0;

    if ((vertex[2] <= _low_bound) || (vertex[2] >= _high_bound)) {
        if (vertex[2] <= _low_bound) step = 1.0 - (vertex[2] - _low_bound) / (0.0 - _low_bound);
        if (vertex[2] >= _high_bound) step = 1.0 - (vertex[2] - _high_bound) / (3.3 - _high_bound);

        vertex[0] = lerp(minor_a, minor_a * squash_equation(), step);
        vertex[1] = lerp(minor_b, minor_b * squash_equation(), step);
    }
    // All encompassing tranformation:
    else {
        vertex[get_minor_axis_a()] *= squash_equation();
        vertex[get_minor_axis_b()] *= squash_equation();
    }
}
