#pragma once

#include "./LineMesh.h"

class LineMeshBuilder {
public:
	static LineMesh createAxisLines(float length);
	static LineMesh ceatePolyline(const std::vector<QVector3D>& points, const QVector3D& color);
};