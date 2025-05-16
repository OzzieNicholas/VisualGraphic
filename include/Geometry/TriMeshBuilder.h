#pragma once
#include "./TriMesh.h"

class TriMesh;

class TriMeshBuilder {
public:
    static TriMesh createGrid(uint rows, uint cols, float size);
    static TriMesh createAxisLines(float length); // 创建三维空间的坐标轴（仅线段）
    static TriMesh createGroundPlane(float size, uint resolution); // 创建Z=0灰色地面（方形网格面）
    static TriMesh createAxisArrow(float radius, float height, int segments); // 创建简单箭头（用小圆锥）
	static TriMesh createPolyline(const std::vector<QVector3D>& points, const QVector3D& color); // 创建折线
};
