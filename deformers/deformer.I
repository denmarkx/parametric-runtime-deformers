/*
* Initializer for Deformer Base.
*/
inline Deformer::Deformer(NodePath& nodePath, Axis axis) {
    _nodePath = nodePath;
    set_axis(axis);
    disassemble_node();
}

/*
* Returns NodePath that is being deformed.
*/
inline NodePath& Deformer::get_node_path() {
    return _nodePath;
}

/*
* Performs deformation using the object's center as the axis.
*/
inline void Deformer::set_other(NodePath& nodePath) {
    _center = nodePath.get_bounds()->as_bounding_sphere()->get_center();
}

/*
* Performs deformation using the given point as the axis.
*/
inline void Deformer::set_other(LPoint3f point) {
    _center = point;
}

/*
* Returns Point3 representing center of object. This is derived from
* the set_other calls or LPoint3::zero if nothing was ever given.
*/
inline LPoint3f Deformer::get_center() {
    return _center;
}

/*
* Sets the major deformation axis and automatically sets the two remaining
* minor axes. Use set_major_axis and set_minor_axis_a/b to override this.
*/
inline void Deformer::set_axis(Axis new_axis) {
    if (!validate_axis(new_axis, "set_axis")) return;
    axis = new_axis;

    // Update the minor axis:
    switch (axis) {
        case Axis::X:
            _minor_axis_a = Axis::Y;
            _minor_axis_b = Axis::Z;
            break;
        case Axis::Y:
            _minor_axis_a = Axis::X;
            _minor_axis_b = Axis::Z;
            break;
        case Axis::Z:
            _minor_axis_a = Axis::X;
            _minor_axis_b = Axis::Y;
            break;
    }
}

/*
* Returns major deformation axis.
*/
inline Axis Deformer::get_axis() const {
    return axis;
}

/*
* Sets the major deformation axis.
* See also: set_axis for automatically setting minor axes.
*/
inline void Deformer::set_major_axis(Axis new_axis) {
    if (!validate_axis(new_axis, "set_major_axis")) return;
    axis = new_axis;
}

/*
* Sets the first minor deformation axis.
* See also: set_axis for automatically setting minor axes.
*/
inline void Deformer::set_minor_axis_a(Axis minor_axis_a) {
    if (!validate_axis(minor_axis_a, "set_minor_axis_a")) return;
    _minor_axis_a = minor_axis_a;
}

/*
* Returns the first minor deformation axis.
*/
inline Axis Deformer::get_minor_axis_a() const {
    return _minor_axis_a;
};

/*
* Sets the second minor deformation axis, if needed by the parametric equation.
* See also: set_axis for automatically setting minor axes.
*/
inline void Deformer::set_minor_axis_b(Axis minor_axis_b) {
    if (!validate_axis(minor_axis_b, "set_minor_axis_b")) return;
    _minor_axis_b = minor_axis_b;
};

/*
* Returns the second minor deformation axis.
*/
inline Axis Deformer::get_minor_axis_b() const {
    return _minor_axis_b;
}

/*
* Ensures given axis is X, Y, or Z.
*/
inline bool Deformer::validate_axis(Axis x, const char* f_name) const {
    if ((x < 0) || (x > 2)) {
        std::cout << f_name << ": Invalid axis (" << x << ")" << "given.\n";
        return false;
    }
    return true;
}