#include "../../include/Utils/UtilsMesh.h"

namespace Utils {

namespace Mesh {

// 网格整体缩放
void scaleMesh(std::vector<QVector3D>& vertices, float factor) {
    for (auto& vertex : vertices) {
        vertex *= factor;
    }
}

// 网格整体平移
void translateMesh(std::vector<QVector3D>& vertices, const QVector3D& translation) {
    for (auto& vertex : vertices) {
        vertex += translation;
    }
}

// 合并两个点集合（适用于非索引类合并，如控制点等）
void mergeMeshes(std::vector<QVector3D>& verticesA, const std::vector<QVector3D>& verticesB) {
    verticesA.insert(
        verticesA.end(),
        verticesB.begin(),
        verticesB.end()
    );
}

// 为三角网格计算顶点法线（基于面法线加权平均）
void computeNormals(std::vector<MeshVertex>& vertices, const std::vector<uint>& indices) {
    for (auto& vertex : vertices) {
        vertex.normal = QVector3D(0, 0, 0);
    }

    for (size_t i = 0; i + 2 < indices.size(); i += 3) {
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

// 将网格中心平移至原点
void centerMesh(std::vector<QVector3D>& vertices) {
    if (vertices.empty()) return;

    QVector3D min = vertices[0];
    QVector3D max = vertices[0];

    for (const auto& v : vertices) {
        min.setX(std::min(min.x(), v.x()));
        min.setY(std::min(min.y(), v.y()));
        min.setZ(std::min(min.z(), v.z()));
        max.setX(std::max(max.x(), v.x()));
        max.setY(std::max(max.y(), v.y()));
        max.setZ(std::max(max.z(), v.z()));
    }

    QVector3D center = (min + max) * 0.5f;
    translateMesh(vertices, -center);
}

// 移除重复顶点（基于误差容忍）
void removeDuplicateVertices(std::vector<QVector3D>& vertices, float tolerance) {
    std::vector<QVector3D> uniques;
    for (const auto& vertex : vertices) {
        bool isDuplicate = false;
        for (const auto& unique : uniques) {
            if ((vertex - unique).lengthSquared() < tolerance * tolerance) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            uniques.push_back(vertex);
        }
    }
    vertices = std::move(uniques);
}

} // namespace Mesh

} // namespace Utils
