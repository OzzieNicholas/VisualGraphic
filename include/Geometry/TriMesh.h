// TriMesh.h
// ����һ���򵥵������������ݽṹ�������������������

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
