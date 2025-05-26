#include "../../include/Geometry/MeshLine.h"

// ========== 构造与析构 ========== //

MeshLine::MeshLine() {
    this->m_drawPrimitiveType = DrawPrimitiveType::Lines;
}

MeshLine::~MeshLine() {

}

// ========== 数据设置与获取 ========== //

// 设置顶点数组
void MeshLine::setVertices(const std::vector<MeshVertex>& vertices) {
    this->m_vertices = vertices;
}

// 设置索引数组
void MeshLine::setIndices(const std::vector<uint>& indices) {
    this->m_indices = indices;
}

// 设置图元类型
void MeshLine::setDrawType(DrawPrimitiveType drawType) {
    this->m_drawPrimitiveType = drawType;
}

// ========== 几何变换与采样 ========== //

// 应用变换矩阵到所有顶点
void MeshLine::applyTransform(const QMatrix4x4& matrix) {
    for (auto& vertex : m_vertices) {
        vertex.position = matrix.map(vertex.position);
    }
}

// 对曲面采样点
std::vector<QVector3D> MeshLine::samplePoints(int count) const {
    std::vector<QVector3D> points;

    if (m_indices.size() < 2 || m_vertices.empty()) {
        return points;
    }

    // 简单采样：取每条线段中点
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

// ========== 导出导入功能 ========== //

// 导出为 JSON 字符串
std::string MeshLine::exportToJson() const {
    return "{}";
}

// 从 JSON 字符串导入
void MeshLine::importFromJson(const std::string& json) {
    
}
