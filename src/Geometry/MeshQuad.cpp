#include "../../include/Geometry/MeshQuad.h"

// ========== ���������� ========== //

MeshQuad::MeshQuad() {
    this->m_drawPrimitiveType = DrawPrimitiveType::Quads;
}

MeshQuad::~MeshQuad() {

}

// ========== �����������ȡ ========== //

// ���ö�������
void MeshQuad::setVertices(const std::vector<MeshVertex>& vertices) {
    this->m_vertices = vertices;
}

// ������������
void MeshQuad::setIndices(const std::vector<uint>& indices) {
    this->m_indices = indices;
}

// ����ͼԪ����
void MeshQuad::setDrawType(DrawPrimitiveType drawType) {
    this->m_drawPrimitiveType = drawType;
}

// ========== ���α任����� ========== //

 // Ӧ�ñ任�������ж���
void MeshQuad::applyTransform(const QMatrix4x4& matrix) {
    for (auto& vertex : this->m_vertices) {
        vertex.position = matrix.map(vertex.position);
        vertex.normal = matrix.mapVector(vertex.normal).normalized();
    }
}

// �����������
std::vector<QVector3D> MeshQuad::samplePoints(int count) const {
    std::vector<QVector3D> result;

    if (this->m_indices.size() < 4 || this->m_vertices.empty()) return result;

    for (size_t i = 0; i + 3 < this->m_indices.size(); i += 4) {
        const QVector3D& a = this->m_vertices[m_indices[i + 0]].position;
        const QVector3D& b = this->m_vertices[m_indices[i + 1]].position;
        const QVector3D& c = this->m_vertices[m_indices[i + 2]].position;
        const QVector3D& d = this->m_vertices[m_indices[i + 3]].position;
        QVector3D center = (a + b + c + d) / 4.0f;
        result.push_back(center);

        if (result.size() >= static_cast<size_t>(count)) break;
    }

    return result;
}

// ========== �������빦�� ========== //

// ����Ϊ JSON �ַ���
std::string MeshQuad::exportToJson() const {
    return "{}";
}

// �� JSON �ַ�������
void MeshQuad::importFromJson(const std::string& json) {

}
