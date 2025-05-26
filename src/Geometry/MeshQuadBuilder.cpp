#include "../../include/Geometry/MeshQuadBuilder.h"

// ���������ı�������XY ƽ�棩
MeshQuad MeshQuadBuilder::buildGridMesh(uint rows, uint cols, float size) {
    MeshQuad mesh;

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
                QVector3D(0.7f, 0.7f, 0.7f)
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
            indices.insert(indices.end(), { i0, i1, i3, i2 });
        }
    }

    mesh.setVertices(vertices);
    mesh.setIndices(indices);
    mesh.setDrawType(DrawPrimitiveType::Quads);
    return mesh;
}

// ��������ƽ�����񣨻�ɫ Z=0 �棩
MeshQuad MeshQuadBuilder::buildGroundPlaneMesh(float size, uint resolution) {
    return buildGridMesh(resolution, resolution, size);
}

// �������� Z ����ı������
MeshQuad MeshQuadBuilder::buildZFacingQuad(float width, float height) {
    MeshQuad mesh;

    float w = width * 0.5f;
    float h = height * 0.5f;

    std::vector<MeshVertex> vertices = {
        { QVector3D(-w, -h, 0), QVector3D(0, 0, 1), QVector3D(1, 1, 1) },
        { QVector3D(w, -h, 0), QVector3D(0, 0, 1), QVector3D(1, 1, 1) },
        { QVector3D(w,  h, 0), QVector3D(0, 0, 1), QVector3D(1, 1, 1) },
        { QVector3D(-w,  h, 0), QVector3D(0, 0, 1), QVector3D(1, 1, 1) }
    };

    std::vector<uint> indices = { 0, 1, 2, 3 };

    mesh.setVertices(vertices);
    mesh.setIndices(indices);
    mesh.setDrawType(DrawPrimitiveType::Quads);
    return mesh;
}

// ���������������棨ÿ��һ���ı��Σ�
MeshQuad MeshQuadBuilder::buildCubeFaceMesh() {
    MeshQuad mesh;
    std::vector<MeshVertex> vertices;
    std::vector<uint> indices;

    const float s = 0.5f;
    QVector3D colors[6] = {
        {1, 0, 0}, {0, 1, 0}, {0, 0, 1},
        {1, 1, 0}, {1, 0, 1}, {0, 1, 1}
    };

    // ÿ�� 4 �����㣬6 �棬�� 24 ������
    QVector3D positions[6][4] = {
        { {-s, -s,  s}, { s, -s,  s}, { s,  s,  s}, {-s,  s,  s} }, // front
        { { s, -s, -s}, {-s, -s, -s}, {-s,  s, -s}, { s,  s, -s} }, // back
        { {-s, -s, -s}, {-s, -s,  s}, {-s,  s,  s}, {-s,  s, -s} }, // left
        { { s, -s,  s}, { s, -s, -s}, { s,  s, -s}, { s,  s,  s} }, // right
        { {-s,  s,  s}, { s,  s,  s}, { s,  s, -s}, {-s,  s, -s} }, // top
        { {-s, -s, -s}, { s, -s, -s}, { s, -s,  s}, {-s, -s,  s} }  // bottom
    };

    for (int f = 0; f < 6; ++f) {
        uint baseIndex = vertices.size();
        for (int i = 0; i < 4; ++i) {
            vertices.push_back({
                positions[f][i],
                {}, // ��ѡ���㷨��
                colors[f]
                });
        }
        indices.insert(indices.end(), {
            baseIndex, baseIndex + 1, baseIndex + 2, baseIndex + 3
            });
    }

    mesh.setVertices(vertices);
    mesh.setIndices(indices);
    mesh.setDrawType(DrawPrimitiveType::Quads);
    return mesh;
}
