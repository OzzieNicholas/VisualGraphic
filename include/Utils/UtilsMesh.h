#pragma once

#include "../Geometry/TriMesh.h"

#include<QMatrix4x4>

namespace Utils {

namespace Mesh {

// 网格整体缩放
void scaleMesh(std::vector<QVector3D>& vertices, float factor);

// 网格整体平移
void translateMesh(std::vector<QVector3D>& vertices, const QVector3D& translation);

// 合并两个点集合（不处理索引偏移，适用于控制点等非拓扑结构）
void mergeMeshes(std::vector<QVector3D>& verticesA, const std::vector<QVector3D>& verticesB);

// 为三角网格计算顶点法线（基于面法线加权平均）
void computeNormals(std::vector<MeshVertex>& vertices, const std::vector<uint>& indices);

// 网格中心化（将中心平移至原点）
void centerMesh(std::vector<QVector3D>& vertices);

// 移除重复顶点（适用于裁剪/布尔等后处理）
void removeDuplicateVertices(std::vector<QVector3D>& vertices, float tolerance = 1e-5f);

} // namespace Mesh

} // namespace Utils
