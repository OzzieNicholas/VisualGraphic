#include "../../include/Geometry/TriMesh.h"

TriMesh::TriMesh() {

}

TriMesh::~TriMesh() {

}

void TriMesh::setVertices(const std::vector<MeshVertex>& vertices) {
    this->vertices = vertices;
}

void TriMesh::setIndices(const std::vector<uint>& indices) {
    this->indices = indices;
}

void TriMesh::setDrawType(DrawPrimitiveType drawType) {
    this->drawPrimitiveType = drawType;
}

const std::vector<MeshVertex>& TriMesh::getVertices() const {
    return vertices;
}

const std::vector<uint>& TriMesh::getIndices() const {
    return indices;
}

DrawPrimitiveType TriMesh::getDrawType() const{
    return DrawPrimitiveType::Triangles;
}

void TriMesh::clear() {
    vertices.clear();
    indices.clear();
}
