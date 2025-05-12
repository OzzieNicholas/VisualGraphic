// TriMesh.h
// ����һ���򵥵������������ݽṹ�������������������

#pragma once

#include "./TriVertex.h"
#include <vector>

class TriMesh {
public:
    std::vector<TriVertex> vertices;
    std::vector<unsigned int> indices;

    void clear();
};
