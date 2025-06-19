#ifndef DEFORMER_H
#define DEFORMER_H

#include "geomVertexRewriter.h"
#include "geomVertexData.h"
#include "geomNode.h"
#include "nodePath.h"
#include "geom.h"
#include "boundingSphere.h"
#include "config_deformer.h"

#include <unordered_map>
#include <array>

#define M_PI 3.14159265358979323846

typedef struct GeomData {
    pvector<LVecBase3f> original_vertices;
    GeomVertexRewriter* vertices;
    GeomVertexRewriter* normals;
} GeomData;

typedef struct DeformerOptions {
    // Name, Ptr->Var, [min, max]
    std::unordered_map<std::string, std::pair<float*, std::vector<double>>> func_map;
} DeformerOptions;

enum Axis: size_t {
    X,
    Y,
    Z,
};

class Deformer {
PUBLISHED:
    inline Deformer(NodePath& nodePath = NodePath(), Axis axis = Axis::X);

    void deform(GeomData* geom_data, double time);
    void deform_all(double time = 0.0);

    inline void set_node_path(NodePath& nodePath);
    inline NodePath& get_node_path();

    inline void set_other(NodePath& nodePath);
    inline void set_other(LPoint3f point);

    inline LPoint3f get_center();

    inline virtual void set_axis(Axis axis);
    inline Axis get_axis() const;

    inline virtual void set_major_axis(Axis axis);

    inline virtual void set_minor_axis_a(Axis minor_axis_a);
    inline Axis get_minor_axis_a() const;

    inline virtual void set_minor_axis_b(Axis minor_axis_b);
    inline Axis get_minor_axis_b() const;

public:
    virtual void update_vertex(LVecBase3f& vertex, LVecBase3f& normals, double time);

    DeformerOptions options;

    Axis _minor_axis_a = Axis::Y;
    Axis _minor_axis_b = Axis::Z;
    Axis axis = Axis::X;

private:
    void disassemble_node();
    inline bool validate_axis(Axis x, const char* f_name) const;

    NodePath _nodePath;
    LPoint3f _center;

    pvector<GeomData*> _vertex_data;
};

#include "deformer.I"

#endif