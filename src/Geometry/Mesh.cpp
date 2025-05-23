#include "../../include/Geometry/Mesh.h"

// ========== �����������ȡ ========== //

// ��ȡ��������
const std::vector<MeshVertex>& Mesh::getVertices() const {
    return m_vertices;
}

// ��ȡ��������
const std::vector<uint>& Mesh::getIndices() const {
    return m_indices;
}

// ��ȡ��ǰ����ͼԪ����
DrawPrimitiveType Mesh::getDrawPrimitiveType() const {
    return m_drawPrimitiveType;
}

// ��ȡ��Χ�У�������С������㣩
std::pair<QVector3D, QVector3D> Mesh::computeBoundingBox() const {
    if (m_vertices.empty()) return { {}, {} };
    QVector3D min = m_vertices[0].position;
    QVector3D max = m_vertices[0].position;
    for (const auto& v : m_vertices) {
        min.setX(std::min(min.x(), v.position.x()));
        min.setY(std::min(min.y(), v.position.y()));
        min.setZ(std::min(min.z(), v.position.z()));
        max.setX(std::max(max.x(), v.position.x()));
        max.setY(std::max(max.y(), v.position.y()));
        max.setZ(std::max(max.z(), v.position.z()));
    }
    return { min, max };
}

// �����������
void Mesh::clearGeometryData() {
    m_vertices.clear();
    m_indices.clear();
}

// ========== ���������ж� ========== //

// �ж϶���������Ƿ���Ч
bool Mesh::hasValidGeometry() const {
    return !m_vertices.empty() && !m_indices.empty();
}

// �ж�ͼ���Ƿ�պ�
bool Mesh::isGeometryClosed() const {
    return false;
}

// �жϼ���ά�ȣ�����2��ʾ��ά���񣬷���3��ʾ��ά
int Mesh::getGeometryDimension() const {
    if (m_vertices.empty()) return 0;
    bool is2D = std::all_of(
        m_vertices.begin(),
        m_vertices.end(),
        [](const MeshVertex& v) {
            return std::abs(v.position.z()) < 1e-6;
        }
    );
    return is2D ? 2 : 3;
}

// �ж��Ƿ������������
bool Mesh::hasNormalData() const {
    return std::any_of(
        m_vertices.begin(),
        m_vertices.end(),
        [](const MeshVertex& v) {
            return !v.normal.isNull();
        }
    );
}

// ======== ���α任����� ======== //

// ������/��������㣨������Ⱦ�򶯻���
std::vector<QVector3D> Mesh::samplePoints(int count) const {
    return {};
}

// ======== ���ӻ� ======== //

// ���ö���״̬����
void Mesh::setAnimationStep(float step) {
    m_animationStep = step;
}

// ��ȡ����״̬����
float Mesh::getAnimationStep() const {
    return m_animationStep;
}

// ======== �������� ======== //

// ����Ϊ SVG ·��

std::string Mesh::exportToSvgPath() const {
    return "{}";
}

// ����Ϊ JSON �ַ���
std::string Mesh::exportToJson() const {
    return "{}";
}

// �� JSON �ַ�������
void Mesh::importFromJson(const std::string&) {
}
