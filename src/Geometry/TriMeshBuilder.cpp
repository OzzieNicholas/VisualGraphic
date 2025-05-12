// TriMeshBuilder.cpp
// 实现标准网格构造函数（如 createGrid），生成规则三角形网格

#include "../../include/Geometry/TriMeshBuilder.h"

TriMesh TriMeshBuilder::createGrid(uint rows, uint cols, float size) {
    TriMesh mesh;

    float half = size * 0.5f;
    float dx = size / (cols - 1);
    float dy = size / (rows - 1);

    // 顶点生成
    for (uint r = 0; r < rows; ++r) {
        for (uint c = 0; c < cols; ++c) {
            float x = -half + c * dx;
            float y = -half + r * dy;
            mesh.vertices.push_back({
                QVector3D(x, y, 0.0f),     // position
                QVector3D(0, 0, 1),        // normal
                QVector3D(0.8f, 0.2f, 0.2f) // color
            });
        }
    }

    // 索引生成（两个三角形组成一个格子）
    for (uint r = 0; r < rows - 1; ++r) {
        for (uint c = 0; c < cols - 1; ++c) {
            uint i0 = r * cols + c;
            uint i1 = i0 + 1;
            uint i2 = i0 + cols;
            uint i3 = i2 + 1;
            mesh.indices.insert(mesh.indices.end(), { i0, i2, i1, i1, i2, i3 });
        }
    }

    return mesh;
}

TriMesh TriMeshBuilder::createAxisLines(float length) {
    TriMesh mesh;
    float L = length;
    mesh.vertices = {
        {{0, 0, 0}, {}, {1, 0, 0}}, {{L, 0, 0}, {}, {1, 0, 0}}, // X - 红
        {{0, 0, 0}, {}, {0, 1, 0}}, {{0, L, 0}, {}, {0, 1, 0}}, // Y - 绿
        {{0, 0, 0}, {}, {0, 0, 1}}, {{0, 0, L}, {}, {0, 0, 1}}  // Z - 蓝
    };
    mesh.indices = { 0, 1, 2, 3, 4, 5 };
    return mesh;
}

TriMesh TriMeshBuilder::createGroundPlane(float size, uint resolution) {
    TriMesh mesh;

    uint rows = resolution;
    uint cols = resolution;
    float half = size * 0.5f;
    float dx = size / (cols - 1);
    float dy = size / (rows - 1);

    for (uint r = 0; r < rows; ++r) {
        for (uint c = 0; c < cols; ++c) {
            float x = -half + c * dx;
            float y = -half + r * dy;
            mesh.vertices.push_back({
                QVector3D(x, y, 0.0f),          // pos
                QVector3D(0, 0, 1),             // normal up
                QVector3D(0.6f, 0.6f, 0.6f)     // gray color
            });
        }
    }

    for (uint r = 0; r < rows - 1; ++r) {
        for (uint c = 0; c < cols - 1; ++c) {
            uint i0 = r * cols + c;
            uint i1 = i0 + 1;
            uint i2 = i0 + cols;
            uint i3 = i2 + 1;
            mesh.indices.insert(mesh.indices.end(), { i0, i2, i1, i1, i2, i3 });
        }
    }

    return mesh;
}

TriMesh TriMeshBuilder::createAxisArrow(float radius, float height, int segments) {
    TriMesh mesh;
    QVector3D tip(0, 0, height);

    for (int i = 0; i < segments; ++i) {
        float theta1 = (float)i / segments * 2.0f * M_PI;
        float theta2 = (float)(i + 1) / segments * 2.0f * M_PI;
        float x1 = radius * std::cos(theta1);
        float y1 = radius * std::sin(theta1);
        float x2 = radius * std::cos(theta2);
        float y2 = radius * std::sin(theta2);

        mesh.vertices.push_back({ tip, {}, {1, 1, 0} });
        mesh.vertices.push_back({ QVector3D(x1, y1, 0), {}, {1, 1, 0} });
        mesh.vertices.push_back({ QVector3D(x2, y2, 0), {}, {1, 1, 0} });

        uint base = i * 3;
        mesh.indices.insert(mesh.indices.end(), { base, base + 1, base + 2 });
    }

    return mesh;
}
