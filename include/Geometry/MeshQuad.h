/*
 * MeshQuad.h：四边形网格类（Mesh 派生类）
 *
 * 功能概述：
 *  - 表示由四边形图元组成的几何网格
 *  - 实现 Mesh 接口，支持变换、采样、导出导入等操作
 *
 * 使用场景：
 *  - 平面结构建模与分块地形展示
 *  - 基于四边形的曲面细分展示与变形演示
 *  - 算法调试中用于四边面元表示与可视化
 */

#pragma once

#include "./Mesh.h"

class MeshQuad : public Mesh {
public:
    // ========== 构造与析构 ========== //

    MeshQuad();
    ~MeshQuad();

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
