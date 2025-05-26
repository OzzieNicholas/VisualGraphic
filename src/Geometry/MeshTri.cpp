#include "../../include/Geometry/MeshTri.h"

// ========== 构造与析构 ========== //

MeshTri::MeshTri() {
    this->m_drawPrimitiveType = DrawPrimitiveType::Triangles;
}

MeshTri::~MeshTri() {

}

// ========== 数据设置与获取 ========== //

// 设置顶点数组
void MeshTri::setVertices(const std::vector<MeshVertex>& vertices) {
    this->m_vertices = vertices;
}

// 设置索引数组
void MeshTri::setIndices(const std::vector<uint>& indices) {
    this->m_indices = indices;
}

// 设置图元类型
void MeshTri::setDrawType(DrawPrimitiveType drawType) {
    if (drawType != DrawPrimitiveType::Triangles) {
        qWarning("MeshTri only supports DrawPrimitiveType::Triangles.");
        return;
    }
    this->m_drawPrimitiveType = drawType;
}

// ========== 几何变换与采样 ========== //

// 应用变换矩阵到所有顶点
void MeshTri::applyTransform(const QMatrix4x4& matrix) {
    for (auto& vertex : m_vertices) {
        vertex.position = matrix.map(vertex.position);
        vertex.normal = matrix.mapVector(vertex.normal).normalized();
    }
}

// 对曲面采样点
std::vector<QVector3D> MeshTri::samplePoints(int count) const {
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

// ========== 导出导入功能 ========== //

// 导出为 JSON 字符串
std::string MeshTri::exportToJson() const {
    return "{}";
}

// 从 JSON 字符串导入
void MeshTri::importFromJson(const std::string& json) {

}