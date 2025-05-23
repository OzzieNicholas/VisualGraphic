#include "../../include/Geometry/LineMeshBuilder.h"

// 构建三维坐标轴线（X/Y/Z 红绿蓝）
LineMesh LineMeshBuilder::buildAxisLines(float length) {
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
    mesh.setDrawType(DrawPrimitiveType::Lines);
    return mesh;
}

// 构建折线（连接给定点集）
LineMesh LineMeshBuilder::buildPolylineMesh(const std::vector<QVector3D>& points, const QVector3D& color) {
    LineMesh mesh;

    std::vector<MeshVertex> vertices;
    for (const auto& point : points) {
        vertices.push_back({ point, {}, color });
    }

    std::vector<uint> indices;
    for (uint i = 0; i < points.size() - 1; ++i) {
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    mesh.setVertices(vertices);
    mesh.setIndices(indices);
    mesh.setDrawType(DrawPrimitiveType::Lines);
    return mesh;
}

// 构建法线线段（从三角网格法线生成）
LineMesh LineMeshBuilder::buildNormalLinesFromTriMesh(const TriMesh& mesh, float scale) {
    LineMesh normalLines;

    const auto& vertices = mesh.getVertices();

    std::vector<MeshVertex> lineVertices;
    std::vector<uint> indices;
    for (uint i = 0; i < vertices.size(); ++i) {
        const auto& v = vertices[i];
        QVector3D p0 = v.position;
        QVector3D p1 = p0 + v.normal.normalized() * scale;

        lineVertices.push_back({ p0, {}, {1.0f, 1.0f, 0.0f} }); // 起点：黄色
        lineVertices.push_back({ p1, {}, {1.0f, 1.0f, 0.0f} }); // 终点：黄色

        indices.push_back(i * 2);
        indices.push_back(i * 2 + 1);
    }

    normalLines.setVertices(lineVertices);
    normalLines.setIndices(indices);
    normalLines.setDrawType(DrawPrimitiveType::Lines);
    return normalLines;
}
