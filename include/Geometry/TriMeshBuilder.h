/*
 * TriMeshBuilder.h：三角网格构造器
 *
 * 功能概述：
 *  - 提供一组静态函数，用于生成各种标准三角形网格几何体
 *  - 所有构造结果均为 TriMesh 类型
 *
 * 使用场景：
 *  - 网格建模与渲染初始化
 *  - 三维坐标场景搭建（如地面、箭头、辅助图元）
 */

#pragma once

#include <cmath>
#include "./TriMesh.h"

class TriMeshBuilder {
public:
    // 构建规则网格（XY平面）
    static TriMesh buildGridMesh(uint rows, uint cols, float size);

    // 构建地面网格（Z=0平面）
    static TriMesh buildGroundPlaneMesh(float size, uint resolution);

    // 构建坐标轴末端箭头
    static TriMesh buildArrowMesh(float radius, float height, int segments);

	// 构建立方体网格
    static TriMesh buildCubeMesh();

	// 构建球体网格
	static TriMesh buildSphereMesh(uint stacks, uint slices);
};
