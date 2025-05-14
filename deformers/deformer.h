#ifndef DEFORMER_H
#define DEFORMER_H

#define M_PI 3.14159265358979323846

#include "geomVertexRewriter.h"
#include "geomVertexData.h"
#include "geomNode.h"
#include "nodePath.h"
#include "geom.h"
#include "boundingSphere.h"

#include <unordered_map>
#include <array>

typedef struct GeomData {
    pvector<LVecBase3f> original_vertices;
    GeomVertexRewriter* vertices;
    GeomVertexRewriter* normals;
    GeomVertexRewriter* tangents;
    GeomVertexRewriter* binormals;
} GeomData;

typedef struct DeformerOptions {
    // Name, Ptr->Var, [min, max]
    std::unordered_map<std::string, std::pair<float*, std::array<double, 2>>> func_map;
} DeformerOptions;


class Deformer {
public:
    inline Deformer(NodePath& nodePath);
    virtual void update_vertex(LVecBase3f& vertex, LVecBase3f& tangent, LVecBase3f& binormal, double time);

    void deform(GeomData* geom_data, double time);
    void deform_all(double time=0.0);

    inline NodePath& get_node_path();
    inline void set_other(NodePath& nodePath);
    inline void set_other(LPoint3f point);
    inline LPoint3f get_center();

    DeformerOptions options;
private:
    void disassemble_node();

private:
    NodePath _nodePath;
    LPoint3f _center;

    pvector<GeomData*> _vertex_data;
};

#include "deformer.I"

#endif