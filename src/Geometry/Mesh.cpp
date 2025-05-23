#include "../../include/Geometry/Mesh.h"

// ========== 数据设置与获取 ========== //

// 获取顶点数组
const std::vector<MeshVertex>& Mesh::getVertices() const {
    return m_vertices;
}

// 获取索引数组
const std::vector<uint>& Mesh::getIndices() const {
    return m_indices;
}

// 获取当前绘制图元类型
DrawPrimitiveType Mesh::getDrawPrimitiveType() const {
    return m_drawPrimitiveType;
}

// 获取包围盒（返回最小点和最大点）
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

// 清空网格数据
void Mesh::clearGeometryData() {
    m_vertices.clear();
    m_indices.clear();
}

// ========== 几何属性判定 ========== //

// 判断顶点和索引是否有效
bool Mesh::hasValidGeometry() const {
    return !m_vertices.empty() && !m_indices.empty();
}

// 判断图形是否闭合
bool Mesh::isGeometryClosed() const {
    return false;
}

// 判断几何维度：返回2表示二维网格，返回3表示三维
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

// 判断是否包含法线数据
bool Mesh::hasNormalData() const {
    return std::any_of(
        m_vertices.begin(),
        m_vertices.end(),
        [](const MeshVertex& v) {
            return !v.normal.isNull();
        }
    );
}

// ======== 几何变换与采样 ======== //

// 对曲线/曲面采样点（用于渲染或动画）
std::vector<QVector3D> Mesh::samplePoints(int count) const {
    return {};
}

// ======== 可视化 ======== //

// 设置动画状态参数
void Mesh::setAnimationStep(float step) {
    m_animationStep = step;
}

// 获取动画状态参数
float Mesh::getAnimationStep() const {
    return m_animationStep;
}

// ======== 导出功能 ======== //

// 导出为 SVG 路径

std::string Mesh::exportToSvgPath() const {
    return "{}";
}

// 导出为 JSON 字符串
std::string Mesh::exportToJson() const {
    return "{}";
}

// 从 JSON 字符串导入
void Mesh::importFromJson(const std::string&) {
}
