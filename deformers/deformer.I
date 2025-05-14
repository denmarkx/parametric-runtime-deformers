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
* Sets major deformation axis.
*/
inline void Deformer::set_axis(Axis axis) {
    _axis = axis;

    // Update the minor axis:
    switch (_axis) {
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
    return _axis;
}
