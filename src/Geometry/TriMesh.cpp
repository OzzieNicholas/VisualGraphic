#include "../../include/Geometry/TriMesh.h"

// ========== 构造与析构 ========== //

TriMesh::TriMesh() {

}

TriMesh::~TriMesh() {

}

// ========== 数据设置与获取 ========== //

// 设置顶点数组
void TriMesh::setVertices(const std::vector<MeshVertex>& vertices) {
    this->vertices = vertices;
}

// 设置索引数组
void TriMesh::setIndices(const std::vector<uint>& indices) {
    this->indices = indices;
}

// 设置图元类型
void TriMesh::setDrawType(DrawPrimitiveType drawType) {
    if (drawType != DrawPrimitiveType::Triangles) {
        qWarning("TriMesh only supports DrawPrimitiveType::Triangles.");
        return;
    }
    this->drawPrimitiveType = drawType;
}

// ========== 几何变换与采样 ========== //

// 应用变换矩阵到所有顶点
void TriMesh::applyTransform(const QMatrix4x4& matrix) {
    for (auto& vertex : vertices) {
        vertex.position = matrix * vertex.position;
        vertex.normal = matrix.mapVector(vertex.normal).normalized();
    }
}

// 对曲面采样点
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

// ========== 导出导入功能 ========== //

// 导出为 JSON 字符串
std::string TriMesh::exportToJson() const {
    // 示例返回空字符串；实际项目可用 QJsonDocument 构建 JSON 表达
    return "{}";
}

// 从 JSON 字符串导入
void TriMesh::importFromJson(const std::string& json) {
    // 示例留空，需实现 JSON 字符串解析（推荐使用 QJsonDocument/QJsonObject）
}