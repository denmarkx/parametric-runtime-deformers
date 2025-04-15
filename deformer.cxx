#include "deformer.h"

/*
* Strips the NodePath given during initializer down to its Geoms.
* Constructs new GeomVertexRewriters for each individual Geom's vertices and normals.
*/
void Deformer::disassemble_node() {
    NodePathCollection collection = _nodePath.find_all_matches("**/+GeomNode");

    // Casting to GeomNode and Geom:
    GeomVertexRewriter *rewriter;
    PT(GeomNode) geom_node;
    PT(Geom) geom;

    // Begin iterating through collection and going down in level:
    for (size_t i = 0; i < collection.get_num_paths(); i++) {
        geom_node = DCAST(GeomNode, collection.get_path(i).node());
        GeomData *geom_data = new GeomData();
        for (size_t j = 0; j < geom_node->get_num_geoms(); j++) {
            // Call modify on this geom so we can keep a hold on a non-const ptr to the GeomVertexData.
            geom = geom_node->modify_geom(j);

            // ..we'll actually hold onto two of the rewriter instances.
            // one for the vertices
            rewriter = new GeomVertexRewriter(geom->modify_vertex_data(), "vertex");
            geom_data->vertices = rewriter;

            // and another for the normals..
            rewriter = new GeomVertexRewriter(geom->modify_vertex_data(), "normals");
            geom_data->normals = rewriter;

            _vertex_data.push_back(geom_data);
        }
    }
}

/*
* Runs deform() on all tracked GeomNodes which had a GeomData
* instance created during disassemble_node().
*/
void Deformer::deform_all() {
    for (GeomData *geom_data : _vertex_data) {
        deform(geom_data);
    }
}

/*
* Deforms the vertices of the given GeomData.
*/
void Deformer::deform(GeomData* geom_data) {
    GeomVertexRewriter* vertices = geom_data->vertices;
    GeomVertexRewriter* normals = geom_data->normals;

    // Default to zero:
    LVecBase3f vertex = LVecBase3f::zero();

    // Iterate through the vertices:
    while (!vertices->is_at_end()) {
        vertex = vertices->get_data3f();
        update_vertex(vertex);

        // Set:
        vertices->set_data3f(vertex);
    }
}

/*
* Individual vertex deformation. <vertex> is updated in-place.
* Children should always override this function specifically.
*/
inline void Deformer::update_vertex(LVecBase3f& vertex) {
}
