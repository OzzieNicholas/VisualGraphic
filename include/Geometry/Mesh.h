/*
 * Mesh.h：网格基类接口定义（抽象基类）
 *
 * 功能概述：
 *  - 提供所有网格类型（如 TriMesh、LineMesh、QuadMesh 等）的统一抽象接口
 *  - 包含顶点、索引、图元类型、动画状态等通用数据成员
 *  - 提供几何访问、变换、判定、导出等接口
 *  - 子类需实现核心纯虚函数，支持自定义构造与渲染
 *
 * 使用场景：
 *  - 几何数据建模（Geometry 模块）
 *  - OpenGL 渲染上传（Renderer 模块）
 *  - 支持拓展到曲线、曲面等类型
 */

#pragma once

#include <vector>
#include <QVector3D>
#include <QMatrix4x4>

// ========== 基本图元类型 ========== //
enum class DrawPrimitiveType {
    Points,
    Lines,
    Triangles,
    Quads,
};

// ========== 顶点数据结构 ========== //
struct MeshVertex {
    QVector3D position;   // 顶点位置
    QVector3D normal;     // 法线向量
    QVector3D color;      // 颜色（RGB）
    QVector3D texCoord;   // 纹理坐标
    QVector3D tangent;    // 切线向量
    QVector3D bitangent;  // 副切线向量
};

// ========== 网格抽象基类 ========== //
class Mesh {
public:
    virtual ~Mesh() = default;

    // ========== 数据设置与获取 ========== //

    // 设置顶点数组
    virtual void setVertices(const std::vector<MeshVertex>& vertices) = 0;

    // 设置索引数组
    virtual void setIndices(const std::vector<uint>& indices) = 0;

    // 设置图元类型
    virtual void setDrawType(DrawPrimitiveType drawType) = 0;

    // 获取顶点数组
    virtual const std::vector<MeshVertex>& getVertices() const;

    // 获取索引数组
    virtual const std::vector<uint>& getIndices() const;

    // 获取当前绘制图元类型
    virtual DrawPrimitiveType getDrawPrimitiveType() const;

    // 获取包围盒
    virtual std::pair<QVector3D, QVector3D> computeBoundingBox() const;

    // 清空网格数据
    virtual void clearGeometryData();

    // ========== 几何属性判定 ========== //

    // 判断顶点和索引是否有效
    virtual bool hasValidGeometry() const;

    // 判断图形是否闭合
    virtual bool isGeometryClosed() const;

    // 判断几何维度：返回2表示二维网格，返回3表示三维
    virtual int getGeometryDimension() const;

    // 判断是否包含法线数据
    virtual bool hasNormalData() const;

    // ======== 几何变换与采样 ======== //

    // 应用变换矩阵到所有顶点
    virtual void applyTransform(const QMatrix4x4& matrix) = 0;

    // 对曲线/曲面采样点（用于渲染或动画）
    virtual std::vector<QVector3D> samplePoints(int count = 100) const;

    // ======== 可视化 ======== //

    // 设置动画状态参数
    virtual void setAnimationStep(float step);

    // 获取动画状态参数
    virtual float getAnimationStep() const;

    // ======== 导出功能 ======== //

    // 导出为 SVG 路径
    virtual std::string exportToSvgPath() const {
        return {};
    }

    // 导出为 JSON 字符串
    virtual std::string exportToJson() const;

    // 从 JSON 字符串导入
    virtual void importFromJson(const std::string&);

protected:
    std::vector<MeshVertex> vertices;       // 顶点数组
    std::vector<uint> indices;              // 索引数组
    DrawPrimitiveType drawPrimitiveType;    // 图元类型
    float animationStep = 0.0f;             // 动画参数（用于插值演示等）
};
