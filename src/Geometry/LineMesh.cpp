#include "../../include/Geometry/LineMesh.h"

LineMesh::LineMesh() {

}

LineMesh::~LineMesh() {

}

void LineMesh::setVertices(const std::vector<MeshVertex>& vertices) {
    this->vertices = vertices;
}

void LineMesh::setIndices(const std::vector<uint>& indices) {
    this->indices = indices;
}

void LineMesh::setDrawType(DrawPrimitiveType drawType) {
    this->drawPrimitiveType = drawType;
}

const std::vector<MeshVertex>& LineMesh::getVertices() const {
    return vertices;
}

const std::vector<uint>& LineMesh::getIndices() const {
    return indices;
}

DrawPrimitiveType LineMesh::getDrawType() const {
    return DrawPrimitiveType::Lines;
}

void LineMesh::clear() {
    vertices.clear();
    indices.clear();
}
