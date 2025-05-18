#pragma once

#include <vector>
#include <QVector3D>

//绘制的基本图元类型
enum class DrawPrimitiveType {
    Points,
    Lines,
    Triangles,
    Quads,
};

// 通用顶点数据结构，包含几何、法线、颜色、纹理等属性
struct MeshVertex {
    QVector3D position;   // 顶点位置
    QVector3D normal;     // 法线向量
    QVector3D color;      // 颜色（RGB）
    QVector3D texCoord;   // 纹理坐标
    QVector3D tangent;    // 切线向量
    QVector3D bitangent;  // 副切线向量
};

// 网格抽象基类：定义所有 Mesh 类型的通用接口
class Mesh {
public:
    virtual ~Mesh() = default;

// 几何数据设置与访问

    // 设置顶点数组
    virtual void setVertices(const std::vector<MeshVertex>& vertices) = 0;

    // 设置索引数组
    virtual void setIndices(const std::vector<uint>& indices) = 0;

    // 设置图元类型
    virtual void setDrawType(DrawPrimitiveType drawType) = 0;

    // 获取顶点数组
    virtual const std::vector<MeshVertex>& getVertices() const = 0;

    // 获取索引数组
    virtual const std::vector<uint>& getIndices() const = 0;

    // 获取当前绘制图元类型
    virtual DrawPrimitiveType getDrawType() const = 0;

    // 清空网格数据
    virtual void clear() = 0;

// 几何属性判定

    // 判断顶点和索引是否有效
    virtual bool isValid() const {
        return !vertices.empty() && !indices.empty();
    }

    // 是否为闭合图形（如闭合曲线、多边形）
    virtual bool isClosed() const {
        return false;
    }

    // 几何维度：返回2表示二维网格，返回3表示三维
    virtual int dimension() const;

    // 是否包含法线数据
    virtual bool hasNormals() const;

    // 获取包围盒（返回最小点和最大点）
    virtual std::pair<QVector3D, QVector3D> getBoundingBox() const;

// 几何变换与采样

    // 应用变换矩阵到所有顶点
    virtual void applyTransform(const QMatrix4x4& matrix) = 0;

    // 对曲线/曲面采样点（用于渲染或动画）
    virtual std::vector<QVector3D> samplePoints(int count = 100) const {
        return {};
    }

// 导出接口（JSON / SVG）

    // 导出为 SVG 路径（如 "M 0 0 L 1 1 ..."）
    virtual std::string toSvgPath() const {
        return {};
    }

    // 导出为 JSON 字符串
    virtual std::string toJson() const {
        return {};
    }

    // 从 JSON 字符串导入
    virtual void fromJson(const std::string&) {}

// 动画支持

    // 设置动画状态（如 t 参数）
    virtual void setAnimationStep(float step) {
        animationStep = step;
    }

    // 获取动画状态参数
    virtual float getAnimationStep() const {
        return animationStep;
    }

protected:
    std::vector<MeshVertex> vertices;       // 顶点数组
    std::vector<uint> indices;              // 索引数组
    DrawPrimitiveType drawPrimitiveType;    // 图元类型
    float animationStep = 0.0f;             // 动画参数（用于插值演示等）
};
