#include "sineDeformer.h"

SineDeformer::SineDeformer(NodePath& nodePath) : Deformer(nodePath) {}

void SineDeformer::update_vertex(LVecBase3f& vertex, double time) {
	// TEST:
	vertex.add_x(sin(time * vertex[0]));
}
