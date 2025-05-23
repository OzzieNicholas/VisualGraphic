/*
 * LineMeshBuilder.h：线段网格构造器
 *
 * 功能概述：
 *  - 提供一组静态函数，用于生成各种线段构成的辅助几何体
 *  - 所有构造结果均为 LineMesh 类型
 *
 * 使用场景：
 *  - 渲染三维坐标轴、法线向量等辅助图元
 *  - 算法过程中的中间线段、折线构造与展示
 *  - 可视化调试与几何分析
 */

#pragma once

#include "./LineMesh.h"
#include "./TriMesh.h"

class LineMeshBuilder {
public:
    // 构建三维坐标轴线（X/Y/Z 红绿蓝）
    static LineMesh buildAxisLines(float length);

    // 构建折线（连接给定点集）
    static LineMesh buildPolylineMesh(const std::vector<QVector3D>& points, const QVector3D& color);

    // 构建法线线段（从三角网格法线生成）
    static LineMesh buildNormalLinesFromTriMesh(const TriMesh& mesh, float scale = 0.1f);
};
