#include "../../include/Geometry/MeshTriBuilder.h"

// 构建规则网格（XY 平面）
MeshTri MeshTriBuilder::buildGridMesh(uint rows, uint cols, float size) {
    MeshTri mesh;

    float half = size * 0.5f;
    float dx = size / (cols - 1);
    float dy = size / (rows - 1);

    std::vector<MeshVertex> vertices;
    for (uint r = 0; r < rows; ++r) {
        for (uint c = 0; c < cols; ++c) {
            float x = -half + c * dx;
            float y = -half + r * dy;
            vertices.push_back({
                QVector3D(x, y, 0.0f),
                QVector3D(0, 0, 1),
                QVector3D(0.8f, 0.8f, 0.8f)
            });
        }
    }

    std::vector<uint> indices;
    for (uint r = 0; r < rows - 1; ++r) {
        for (uint c = 0; c < cols - 1; ++c) {
            uint i0 = r * cols + c;
            uint i1 = i0 + 1;
            uint i2 = i0 + cols;
            uint i3 = i2 + 1;
            indices.insert(
                indices.end(),
                { i0, i2, i1, i1, i2, i3 }
            );
        }
    }

    mesh.setVertices(vertices);
    mesh.setIndices(indices);
    mesh.setDrawType(DrawPrimitiveType::Triangles);
    return mesh;
}

// 构建地面网格（Z=0平面）
MeshTri MeshTriBuilder::buildGroundPlaneMesh(float size, uint resolution) {
    return buildGridMesh(resolution, resolution, size);
}

// 构建坐标轴末端箭头
MeshTri MeshTriBuilder::buildArrowMesh(float radius, float height, int segments) {
    MeshTri mesh;
    QVector3D tip(0, 0, height);

    std::vector<MeshVertex> vertices;
    std::vector<uint> indices;

    for (int i = 0; i < segments; ++i) {
        float theta1 = (float)i / segments * 2.0f * M_PI;
        float theta2 = (float)(i + 1) / segments * 2.0f * M_PI;
        float x1 = radius * std::cos(theta1);
        float y1 = radius * std::sin(theta1);
        float x2 = radius * std::cos(theta2);
        float y2 = radius * std::sin(theta2);

        vertices.push_back({ tip, {}, {1, 1, 0} });
        vertices.push_back({ QVector3D(x1, y1, 0), {}, {1, 1, 0} });
        vertices.push_back({ QVector3D(x2, y2, 0), {}, {1, 1, 0} });

        uint base = i * 3;
        indices.insert(indices.end(), { base, base + 1, base + 2 });
    }

    mesh.setVertices(vertices);
    mesh.setIndices(indices);
    mesh.setDrawType(DrawPrimitiveType::Triangles);
    return mesh;
}

// 构建立方体网格
MeshTri MeshTriBuilder::buildCubeMesh() {
    MeshTri mesh;

    const QVector3D normals[] = {
        { 0,  0,  1}, { 0,  0, -1},
        {-1,  0,  0}, { 1,  0,  0},
        { 0,  1,  0}, { 0, -1,  0}
    };

    const QVector3D colors[] = {
        {1, 0, 0}, {0, 1, 0},
        {0, 0, 1}, {1, 1, 0},
        {1, 0, 1}, {0, 1, 1}
    };

    const QVector3D positions[] = {
        // 前 (+Z)
        {-0.5, -0.5,  0.5}, { 0.5, -0.5,  0.5}, { 0.5,  0.5,  0.5}, {-0.5,  0.5,  0.5},
        // 后(-Z)
        { 0.5, -0.5, -0.5}, {-0.5, -0.5, -0.5}, {-0.5,  0.5, -0.5}, { 0.5,  0.5, -0.5},
        // 左 (-X)
        {-0.5, -0.5, -0.5}, {-0.5, -0.5,  0.5}, {-0.5,  0.5,  0.5}, {-0.5,  0.5, -0.5},
        // 右 (+X)
        { 0.5, -0.5,  0.5}, { 0.5, -0.5, -0.5}, { 0.5,  0.5, -0.5}, { 0.5,  0.5,  0.5},
        // 上 (+Y)
        {-0.5,  0.5,  0.5}, { 0.5,  0.5,  0.5}, { 0.5,  0.5, -0.5}, {-0.5,  0.5, -0.5},
        // 下 (-Y)
        {-0.5, -0.5, -0.5}, { 0.5, -0.5, -0.5}, { 0.5, -0.5,  0.5}, {-0.5, -0.5,  0.5}
    };

    std::vector<MeshVertex> vertices;
    for (int i = 0; i < 6; ++i) {
        int base = i * 4;
        for (int j = 0; j < 4; ++j) {
            vertices.push_back({
                positions[base + j],
                normals[i],
                colors[i]
            });
        }
    }

    std::vector<uint> indices;
    for (uint i = 0; i < 6; ++i) {
        uint base = i * 4;
        indices.insert(indices.end(), {
            base, base + 1, base + 2,
            base, base + 2, base + 3
        });
    }

    mesh.setVertices(vertices);
    mesh.setIndices(indices);
    mesh.setDrawType(DrawPrimitiveType::Triangles);
    return mesh;
}

// 构建球体网格
MeshTri MeshTriBuilder::buildSphereMesh(uint stacks, uint slices) {
    MeshTri mesh;
    std::vector<MeshVertex> vertices;
    std::vector<uint> indices;

    for (uint i = 0; i <= stacks; ++i) {
        float v = float(i) / stacks;
        float phi = v * M_PI;

        for (uint j = 0; j <= slices; ++j) {
            float u = float(j) / slices;
            float theta = u * 2.0f * M_PI;

            float x = std::sin(phi) * std::cos(theta);
            float y = std::cos(phi);
            float z = std::sin(phi) * std::sin(theta);

            QVector3D pos(x, y, z);
            vertices.push_back({
                pos,
                pos.normalized(), // 法线即为位置方向
                {1.0f - u, v, u} // 颜色按经纬度渐变
            });
        }
    }

    for (uint i = 0; i < stacks; ++i) {
        for (uint j = 0; j < slices; ++j) {
            uint row1 = i * (slices + 1);
            uint row2 = (i + 1) * (slices + 1);

            indices.insert(indices.end(), {
                row1 + j, row2 + j, row2 + j + 1,
                row1 + j, row2 + j + 1, row1 + j + 1
            });
        }
    }

    mesh.setVertices(vertices);
    mesh.setIndices(indices);
    mesh.setDrawType(DrawPrimitiveType::Triangles);
    return mesh;
}
