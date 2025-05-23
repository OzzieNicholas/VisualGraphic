#include "../../include/Geometry/TriMesh.h"

// ========== ���������� ========== //

TriMesh::TriMesh() {
    this->m_drawPrimitiveType = DrawPrimitiveType::Triangles;
}

TriMesh::~TriMesh() {

}

// ========== �����������ȡ ========== //

// ���ö�������
void TriMesh::setVertices(const std::vector<MeshVertex>& vertices) {
    this->m_vertices = vertices;
}

// ������������
void TriMesh::setIndices(const std::vector<uint>& indices) {
    this->m_indices = indices;
}

// ����ͼԪ����
void TriMesh::setDrawType(DrawPrimitiveType drawType) {
    if (drawType != DrawPrimitiveType::Triangles) {
        qWarning("TriMesh only supports DrawPrimitiveType::Triangles.");
        return;
    }
    this->m_drawPrimitiveType = drawType;
}

// ========== ���α任����� ========== //

// Ӧ�ñ任�������ж���
void TriMesh::applyTransform(const QMatrix4x4& matrix) {
    for (auto& vertex : m_vertices) {
        vertex.position = matrix.map(vertex.position);
        vertex.normal = matrix.mapVector(vertex.normal).normalized();
    }
}

// �����������
std::vector<QVector3D> TriMesh::samplePoints(int count) const {
    std::vector<QVector3D> result;
    if (m_indices.size() < 3 || m_vertices.empty()) return result;

    for (size_t i = 0; i + 2 < m_indices.size() && result.size() < size_t(count); i += 3) {
        const QVector3D& a = m_vertices[m_indices[i]].position;
        const QVector3D& b = m_vertices[m_indices[i + 1]].position;
        const QVector3D& c = m_vertices[m_indices[i + 2]].position;
        QVector3D centroid = (a + b + c) / 3.0f;
        result.push_back(centroid);
    }
    return result;
}

// ========== �������빦�� ========== //

// ����Ϊ JSON �ַ���
std::string TriMesh::exportToJson() const {
    return "{}";
}

// �� JSON �ַ�������
void TriMesh::importFromJson(const std::string& json) {

}