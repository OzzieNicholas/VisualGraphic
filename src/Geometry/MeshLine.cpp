#include "../../include/Geometry/MeshLine.h"

// ========== ���������� ========== //

MeshLine::MeshLine() {
    this->m_drawPrimitiveType = DrawPrimitiveType::Lines;
}

MeshLine::~MeshLine() {

}

// ========== �����������ȡ ========== //

// ���ö�������
void MeshLine::setVertices(const std::vector<MeshVertex>& vertices) {
    this->m_vertices = vertices;
}

// ������������
void MeshLine::setIndices(const std::vector<uint>& indices) {
    this->m_indices = indices;
}

// ����ͼԪ����
void MeshLine::setDrawType(DrawPrimitiveType drawType) {
    this->m_drawPrimitiveType = drawType;
}

// ========== ���α任����� ========== //

// Ӧ�ñ任�������ж���
void MeshLine::applyTransform(const QMatrix4x4& matrix) {
    for (auto& vertex : m_vertices) {
        vertex.position = matrix.map(vertex.position);
    }
}

// �����������
std::vector<QVector3D> MeshLine::samplePoints(int count) const {
    std::vector<QVector3D> points;

    if (m_indices.size() < 2 || m_vertices.empty()) {
        return points;
    }

    // �򵥲�����ȡÿ���߶��е�
    for (size_t i = 0; i + 1 < m_indices.size(); i += 2) {
        const QVector3D& a = m_vertices[m_indices[i]].position;
        const QVector3D& b = m_vertices[m_indices[i + 1]].position;
        points.push_back((a + b) * 0.5f);

        if (points.size() >= static_cast<size_t>(count)) {
            break;
        }
    }

    return points;
}

// ========== �������빦�� ========== //

// ����Ϊ JSON �ַ���
std::string MeshLine::exportToJson() const {
    return "{}";
}

// �� JSON �ַ�������
void MeshLine::importFromJson(const std::string& json) {
    
}
