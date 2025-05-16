// TriMesh.h
// 定义一个简单的三角网格数据结构，包括顶点和索引数组

#pragma once

#include <QVector3D>
#include <QOpenGLWidget>

enum class DrawPrimitiveType {
    Points,
    Lines,
    Triangles,
    Quads,
};

struct TriVertex {
    QVector3D position;
    QVector3D normal;
    QVector3D color;
    QVector3D texCoord;
    QVector3D tangent;
    QVector3D bitangent;
};

class TriMesh {
public:
    std::vector<TriVertex> vertices;
    std::vector<unsigned int> indices;
    DrawPrimitiveType drawPrimitiveType = DrawPrimitiveType::Triangles;

    void clear();
};
