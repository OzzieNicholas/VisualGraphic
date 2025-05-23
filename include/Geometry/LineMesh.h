/*
 * LineMesh.h：线段网格类（Mesh 派生类）
 *
 * 功能概述：
 *  - 表示由线段图元构成的轻量网格
 *  - 支持用于显示坐标轴、法线向量、折线等辅助信息
 *
 * 使用场景：
 *  - 可视化辅助图元（如坐标系）
 *  - 算法调试过程中的边缘结构展示
 *  - 渲染法线、连接路径、边界线等
 */

#pragma once

#include "./Mesh.h"

class LineMesh : public Mesh {
public:
    // ========== 构造与析构 ========== //

    LineMesh();
    ~LineMesh();

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
