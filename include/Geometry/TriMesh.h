// TriMesh.h
// ����һ���򵥵������������ݽṹ�������������������

#pragma once

#include "./TriVertex.h"

class TriMesh {
public:
    std::vector<TriVertex> vertices;
    std::vector<unsigned int> indices;

    GLenum primitiveType = GL_TRIANGLES;

    void clear();
};
