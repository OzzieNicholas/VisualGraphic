// TriMesh.h
// 定义一个简单的三角网格数据结构，包括顶点和索引数组

#pragma once

#include "../CommonIncludes.h"

struct TriVertex {
    QVector3D position;
    QVector3D normal;
    QVector3D color;
};

class TriMesh {
public:
    std::vector<TriVertex> vertices;
    std::vector<unsigned int> indices;

    GLenum primitiveType = GL_TRIANGLES;

    void clear();
};
