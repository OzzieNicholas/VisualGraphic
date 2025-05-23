/*
 * TriMesh.h：三角形网格类（Mesh 派生类）
 *
 * 功能概述：
 *  - 实现 Mesh 接口，专用于三角形图元类型的网格表示
 *  - 用于表面建模、可视化、采样、动画变换等任务
 *
 * 特性说明：
 *  - 默认图元类型固定为 DrawPrimitiveType::Triangles
 *  - 支持基本几何操作、顶点变换、导入导出等接口
 */

#pragma once

#include "./Mesh.h"

class TriMesh : public Mesh {
public:
    // ========== 构造与析构 ========== //

    TriMesh();
    ~TriMesh();

    // ========== 数据设置与获取 ========== //

    // 设置顶点数组
    void setVertices(const std::vector<MeshVertex>& vertices) override;

    // 设置索引数组
    void setIndices(const std::vector<uint>& indices) override;

    // 设置图元类型
    void setDrawType(DrawPrimitiveType drawType) override;

    // ========== 几何变换与采样 ========== //

    // 应用变换矩阵到所有顶点
    void applyTransform(const QMatrix4x4& matrix) override;

    // 对曲面采样点
    std::vector<QVector3D> samplePoints(int count = 100) const override;

    // ========== 导出导入功能 ========== //

    // 导出为 JSON 字符串
    std::string exportToJson() const override;

    // 从 JSON 字符串导入
    void importFromJson(const std::string& json) override;
};
