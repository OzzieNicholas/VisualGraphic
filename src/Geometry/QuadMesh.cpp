#include "../../include/Geometry/QuadMesh.h"

QuadMesh::QuadMesh() {

}

QuadMesh::~QuadMesh() {

}

void QuadMesh::setVertices(const std::vector<MeshVertex>& vertices) {
    this->vertices = vertices;
}

void QuadMesh::setIndices(const std::vector<unsigned int>& indices) {
    this->indices = indices;
}

void QuadMesh::setDrawType(DrawPrimitiveType drawType) {
    this->drawPrimitiveType = drawType;
}

const std::vector<MeshVertex>& QuadMesh::getVertices() const {
    return vertices;
}

const std::vector<uint>& QuadMesh::getIndices() const {
    return indices;
}

DrawPrimitiveType QuadMesh::getDrawType() const {
    return DrawPrimitiveType::Quads;
}

void QuadMesh::clear() {
    vertices.clear();
    indices.clear();
}
