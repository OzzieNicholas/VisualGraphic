/*
 * MeshQuadBuilder.h：四边形网格构造器
 *
 * 功能概述：
 *  - 提供一组静态函数，用于构造常见的四边形网格几何结构
 *  - 所有构造结果均为 MeshQuad 类型
 *
 * 使用场景：
 *  - 规则地形构建（如地砖、地板、棋盘格）
 *  - 基于四边形结构的离散曲面表示
 *  - 支持细分曲面算法、几何建模等图形处理
 */

#pragma once

#include "./MeshQuad.h"
#include <cmath>

class MeshQuadBuilder {
public:
    // 构建规则四边形网格（XY 平面）
    static MeshQuad buildGridMesh(uint rows, uint cols, float size);

    // 构建地面平面网格（灰色 Z=0 面）
    static MeshQuad buildGroundPlaneMesh(float size, uint resolution);

    // 构建面向 Z 轴的四边面板
    static MeshQuad buildZFacingQuad(float width, float height);

    // 构建四边形立方体展开结构（六面分布）
    static MeshQuad buildCubeFaceMesh();
};
