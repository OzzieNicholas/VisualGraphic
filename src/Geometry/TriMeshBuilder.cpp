#include "../../include/Geometry/TriMeshBuilder.h"

TriMesh TriMeshBuilder::createGrid(uint rows, uint cols, float size) {
    TriMesh mesh;

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
                QVector3D(0.8f, 0.2f, 0.2f)
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
            indices.insert(indices.end(), { i0, i2, i1, i1, i2, i3 });
        }
    }

    mesh.setVertices(vertices);
    mesh.setIndices(indices);

    return mesh;
}

TriMesh TriMeshBuilder::createAxisLines(float length) {
    TriMesh mesh;

    std::vector<MeshVertex> vertices = {
        {{0, 0, 0}, {}, {1, 0, 0}}, {{length, 0, 0}, {}, {1, 0, 0}}, // X - ºì
        {{0, 0, 0}, {}, {0, 1, 0}}, {{0, length, 0}, {}, {0, 1, 0}}, // Y - ÂÌ
        {{0, 0, 0}, {}, {0, 0, 1}}, {{0, 0, length}, {}, {0, 0, 1}}  // Z - À¶
    };

    std::vector<uint> indices = { 0, 1, 2, 3, 4, 5 };

    DrawPrimitiveType drawPrimitiveType = DrawPrimitiveType::Lines;

    mesh.setVertices(vertices);
    mesh.setIndices(indices);
    mesh.setDrawType(drawPrimitiveType);
    
    return mesh;
}

TriMesh TriMeshBuilder::createGroundPlane(float size, uint resolution) {
    TriMesh mesh;

    uint rows = resolution;
    uint cols = resolution;
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
                QVector3D(0.6f, 0.6f, 0.6f)
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
            indices.insert(indices.end(), { i0, i2, i1, i1, i2, i3 });
        }
    }

    mesh.setVertices(vertices);
    mesh.setIndices(indices);

    return mesh;
}

TriMesh TriMeshBuilder::createAxisArrow(float radius, float height, int segments) {
    TriMesh mesh;
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

    return mesh;
}

TriMesh TriMeshBuilder::createPolyline(const std::vector<QVector3D>& points, const QVector3D& color) {
	TriMesh mesh;

    std::vector<MeshVertex> vertices;
	for (const auto& point : points) {
		vertices.push_back({ point, {}, color });
	}
    
    std::vector<uint> indices;
	for (uint i = 0; i < points.size() - 1; ++i) {
        indices.push_back(i);
        indices.push_back(i + 1);
	}
    
    DrawPrimitiveType drawPrimitiveType = DrawPrimitiveType::Lines;

    mesh.setVertices(vertices);
    mesh.setIndices(indices);
    mesh.setDrawType(drawPrimitiveType);

	return mesh;
}
