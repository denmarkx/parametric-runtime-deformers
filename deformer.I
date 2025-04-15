/*
* Initializer for Deformer Base.
*/
inline Deformer::Deformer(NodePath& nodePath) {
    _nodePath = nodePath;
    disassemble_node();
}
