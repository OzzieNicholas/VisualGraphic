#include "../../include/Geometry/TriMesh.h"

// ========== ���������� ========== //

TriMesh::TriMesh() {

}

TriMesh::~TriMesh() {

}

// ========== �����������ȡ ========== //

// ���ö�������
void TriMesh::setVertices(const std::vector<MeshVertex>& vertices) {
    this->vertices = vertices;
}

// ������������
void TriMesh::setIndices(const std::vector<uint>& indices) {
    this->indices = indices;
}

// ����ͼԪ����
void TriMesh::setDrawType(DrawPrimitiveType drawType) {
    if (drawType != DrawPrimitiveType::Triangles) {
        qWarning("TriMesh only supports DrawPrimitiveType::Triangles.");
        return;
    }
    this->drawPrimitiveType = drawType;
}

// ========== ���α任����� ========== //

// Ӧ�ñ任�������ж���
void TriMesh::applyTransform(const QMatrix4x4& matrix) {
    for (auto& vertex : vertices) {
        vertex.position = matrix * vertex.position;
        vertex.normal = matrix.mapVector(vertex.normal).normalized();
    }
}

// �����������
std::vector<QVector3D> TriMesh::samplePoints(int count) const {
    std::vector<QVector3D> result;
    if (indices.size() < 3 || vertices.empty()) return result;

    for (size_t i = 0; i + 2 < indices.size() && result.size() < size_t(count); i += 3) {
        const QVector3D& a = vertices[indices[i]].position;
        const QVector3D& b = vertices[indices[i + 1]].position;
        const QVector3D& c = vertices[indices[i + 2]].position;
        QVector3D centroid = (a + b + c) / 3.0f;
        result.push_back(centroid);
    }
    return result;
}

// ========== �������빦�� ========== //

// ����Ϊ JSON �ַ���
std::string TriMesh::exportToJson() const {
    // ʾ�����ؿ��ַ�����ʵ����Ŀ���� QJsonDocument ���� JSON ���
    return "{}";
}

// �� JSON �ַ�������
void TriMesh::importFromJson(const std::string& json) {
    // ʾ�����գ���ʵ�� JSON �ַ����������Ƽ�ʹ�� QJsonDocument/QJsonObject��
}