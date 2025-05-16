#include "../../include/Geometry/LineMeshBuilder.h"

LineMesh LineMeshBuilder::createAxisLines(float length) {
    LineMesh mesh;

    std::vector<MeshVertex> vertices = {
        { QVector3D(0.0f, 0.0f, 0.0f), {}, QVector3D(1.0f, 0.0f, 0.0f) },
        { QVector3D(length, 0.0f, 0.0f), {}, QVector3D(1.0f, 0.0f, 0.0f) },
        { QVector3D(0.0f, 0.0f, 0.0f), {}, QVector3D(0.0f, 1.0f, 0.0f) },
        { QVector3D(0.0f, length, 0.0f), {}, QVector3D(0.0f, 1.0f, 0.0f) },
        { QVector3D(0.0f, 0.0f, 0.0f), {}, QVector3D(0.0f, 0.0f, 1.0f) },
        { QVector3D(0.0f, 0.0f, length), {}, QVector3D(0.0f, 0.0f, 1.0f) },
    };

    std::vector<uint> indices = { 0, 1, 2, 3, 4, 5 };

    mesh.setVertices(vertices);
    mesh.setIndices(indices);

    return mesh;
}

LineMesh LineMeshBuilder::ceatePolyline(const std::vector<QVector3D>& points, const QVector3D& color) {
    LineMesh mesh;

    std::vector<MeshVertex> vertices;
    for (const auto& point : points) {
        vertices.push_back({ point, {}, color });
    }

    std::vector<uint> indices;
    for (size_t i = 0; i < points.size() - 1; ++i) {
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    mesh.setVertices(vertices);
    mesh.setIndices(indices);

    return mesh;
}
