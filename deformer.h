#ifndef DEFORMER_H
#define DEFORMER_H

#include "geomVertexRewriter.h"
#include "geomVertexData.h"
#include "geomNode.h"
#include "nodePath.h"
#include "geom.h"

typedef struct GeomData {
    GeomVertexRewriter* vertices;
    GeomVertexRewriter* normals;
} GeomData;

class Deformer {
public:
    inline Deformer(NodePath& nodePath);
    inline void update_vertex(LVecBase3f& vertex);

    void deform(GeomData* geom_data);
    void deform_all();

private:
    void disassemble_node();

private:
    NodePath _nodePath;

    pvector<GeomData*> _vertex_data;
};

#include "deformer.I"

#endif