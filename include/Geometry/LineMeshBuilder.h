#pragma once

#include "./LineMesh.h"

class LineMeshBuilder {
public:
	static LineMesh createAxisLines(float length);
	static LineMesh createPolyline(const std::vector<QVector3D>& points, const QVector3D& color);
};