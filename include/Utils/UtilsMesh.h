#pragma once

#include<vector>
#include<QVector3D>
#include<QMatrix4x4>

namespace Utils {

namespace Mesh {

inline void scaleMesh(std::vector<QVector3D>& vertices, float factor) {
	for (auto& vertex : vertices) {
		vertex *= factor;
	}
}

inline void translateMesh(std::vector<QVector3D>& vertices, const QVector3D& translation) {
	for (auto& vertex : vertices) {
		vertex += translation;
	}
}

inline void mergeMeshs(std::vector<QVector3D>& vertices1, std::vector<QVector3D>& vertices2) {
	vertices1.insert(vertices1.end(), vertices2.begin(), vertices2.end());
}

} // namespace Mesh

} // namespace Utils