#include "../../include/Geometry/QuadMesh.h"

// ========== 构造与析构 ========== //

QuadMesh::QuadMesh() {
    this->m_drawPrimitiveType = DrawPrimitiveType::Quads;
}

QuadMesh::~QuadMesh() {

}

// ========== 数据设置与获取 ========== //

// 设置顶点数组
void QuadMesh::setVertices(const std::vector<MeshVertex>& vertices) {
    this->m_vertices = vertices;
}

// 设置索引数组
void QuadMesh::setIndices(const std::vector<uint>& indices) {
    this->m_indices = indices;
}

// 设置图元类型
void QuadMesh::setDrawType(DrawPrimitiveType drawType) {
    this->m_drawPrimitiveType = drawType;
}

// ========== 几何变换与采样 ========== //

 // 应用变换矩阵到所有顶点
void QuadMesh::applyTransform(const QMatrix4x4& matrix) {
    for (auto& vertex : this->m_vertices) {
        vertex.position = matrix.map(vertex.position);
        vertex.normal = matrix.mapVector(vertex.normal).normalized();
    }
}

// 对曲面采样点
std::vector<QVector3D> QuadMesh::samplePoints(int count) const {
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

// ========== 导出导入功能 ========== //

// 导出为 JSON 字符串
std::string QuadMesh::exportToJson() const {
    return "{}";
}

// 从 JSON 字符串导入
void QuadMesh::importFromJson(const std::string& json) {

}
