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

            // While we're here, we're gonna get the defaults.
            LVecBase3f vertex = LVecBase3f::zero();
            while (!rewriter->is_at_end()) {
                vertex = rewriter->get_data3f();
                geom_data->original_vertices.push_back(vertex);
            }

            // and another for the normals..
            rewriter = new GeomVertexRewriter(geom->modify_vertex_data(), "normal");
            geom_data->normals = rewriter;

            // and another for the tangents..
            rewriter = new GeomVertexRewriter(geom->modify_vertex_data(), InternalName::get_tangent());
            geom_data->tangents = rewriter;

            // and another for the binormals..
            rewriter = new GeomVertexRewriter(geom->modify_vertex_data(), InternalName::get_binormal());
            geom_data->binormals = rewriter;

            _vertex_data.push_back(geom_data);
        }
    }
}

/*
* Runs deform() on all tracked GeomNodes which had a GeomData
* instance created during disassemble_node().
*/
void Deformer::deform_all(double time) {
    for (GeomData *geom_data : _vertex_data) {
        deform(geom_data, time);
    }
}

/*
* Deforms the vertices of the given GeomData.
*/
void Deformer::deform(GeomData* geom_data, double time) {
    GeomVertexRewriter* vertices = geom_data->vertices;
    GeomVertexRewriter* normals = geom_data->normals;
    GeomVertexRewriter* tangents = geom_data->tangents;
    GeomVertexRewriter* binormals = geom_data->binormals;

    // Default to zero:
    LVecBase3f vertex = LVecBase3f::zero();
    LVecBase3f normal = LVecBase3f::zero();
    LVecBase3f binormal = LVecBase3f::zero();
    LVecBase3f tangent = LVecBase3f::zero();

    // Reset rows.
    vertices->set_row(0);
    normals->set_row(0);
    tangents->set_row(0);
    binormals->set_row(0);

    // Iterate through the vertices:
    size_t index = 0;
    while (!vertices->is_at_end()) {
        vertex = geom_data->original_vertices[index];
        if (!tangents->is_at_end()) {
            tangent = tangents->get_data3f();
        }
        if (!binormals->is_at_end()) {
            binormal = binormals->get_data3f();
        }
        update_vertex(vertex, tangent, binormal, time);

        // Set:
        vertices->set_data3f(vertex);
        // TODO: normals->set_data3f(tangent.cross(binormal).normalize());
        if (!tangents->is_at_end()) {
            tangents->set_data3f(tangent);
        }
        if (!binormals->is_at_end()) {
            binormals->set_data3f(binormal);
        }
        index++;
    }
}

/*
* Individual vertex deformation. <vertex> is updated in-place.
* Children should always override this function specifically.
*/
void Deformer::update_vertex(LVecBase3f& vertex, LVecBase3f& tangent, LVecBase3f& binormal, double time) {}
