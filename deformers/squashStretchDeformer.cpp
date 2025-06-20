#include "squashStretchDeformer.h"

/*
* Squashes and stretches an object based on arbitrary scale.
*/
SquashStretchDeformer::SquashStretchDeformer(NodePath& nodePath, Axis axis) : Deformer(nodePath, axis) {
    options.func_map = {
        {"Scale", { &_scale, {0.001, 10.0} } },
        {"Expand", { &_expand, {0.001, 10.0} } },
        {"Low Bound", { &_low_bound, {-5, 5.0} } },
        {"High Bound", { &_high_bound, {0, 5.0} } },
    };

    // Initialize low and high bound as what it currently is
    LPoint3f _min, _max;
    get_node_path().calc_tight_bounds(_min, _max);
    _low_bound = _min[axis]; _high_bound = _max[axis];

}

/*
* Recalculates the minimum and maximum of the mesh and modifies
* the thresholds for the function map.
*/
inline void SquashStretchDeformer::set_axis(Axis new_axis) {
    Deformer::set_axis(new_axis);

    LPoint3f _min, _max;
    get_node_path().calc_tight_bounds(_min, _max);
    _bottom = _min[new_axis]; _top = _max[new_axis];

    options.func_map["Low Bound"].second = { _bottom, _top };
    options.func_map["High Bound"].second = { _bottom, _top };
    std::cout << _bottom << "  " << _top << "\n";
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

    if ((major <= _low_bound) || (major >= _high_bound)) {
        if (major <= _low_bound) step = 1.0 - (major - _low_bound) / (_bottom - _low_bound);
        if (major >= _high_bound) step = 1.0 - (major - _high_bound) / (_top - _high_bound);

        vertex[get_minor_axis_a()] = lerp(minor_a, minor_a * squash_equation(), step);
        vertex[get_minor_axis_b()] = lerp(minor_b, minor_b * squash_equation(), step);
    }
    // All encompassing tranformation:
    else {
        vertex[get_minor_axis_a()] *= squash_equation();
        vertex[get_minor_axis_b()] *= squash_equation();
    }
}
