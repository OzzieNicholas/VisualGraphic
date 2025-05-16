#pragma once

#include "../Geometry/TriMesh.h"

#include<QMatrix4x4>

namespace Utils {

namespace Mesh {

inline void scaleMesh(std::vector<QVector3D>& vertices, float factor) {
	std::transform(
		vertices.begin(),
		vertices.end(),
		vertices.begin(),
		[factor](QVector3D& vertex) {
			return vertex * factor;
		}
	);
}

inline void translateMesh(std::vector<QVector3D>& vertices, const QVector3D& translation) {
	std::transform(
		vertices.begin(),
		vertices.end(),
		vertices.begin(),
		[&translation](QVector3D& vertex) {
			return vertex + translation;
		}
	);
}

inline void mergeMeshes(std::vector<QVector3D>& vertices1, std::vector<QVector3D>& vertices2) {
	vertices1.insert(vertices1.end(), vertices2.begin(), vertices2.end());
}

inline void computeNormals(std::vector<TriVertex>& vertices, const std::vector<uint>& indices) {
	for (size_t i = 0; i < indices.size(); i += 3) {
		uint idx0 = indices[i];
		uint idx1 = indices[i + 1];
		uint idx2 = indices[i + 2];

		QVector3D v0 = vertices[idx0].position;
		QVector3D v1 = vertices[idx1].position;
		QVector3D v2 = vertices[idx2].position;

		QVector3D normal = QVector3D::normal(v1 - v0, v2 - v0);

		vertices[idx0].normal += normal;
		vertices[idx1].normal += normal;
		vertices[idx2].normal += normal;
	}
	for (auto& vertex : vertices) {
		vertex.normal.normalize();
	}
}

} // namespace Mesh

} // namespace Utils