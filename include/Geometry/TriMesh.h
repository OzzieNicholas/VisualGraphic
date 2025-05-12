// TriMesh.h
// 定义一个简单的三角网格数据结构，包括顶点和索引数组

#pragma once

#include "./TriVertex.h"
#include <vector>

class TriMesh {
public:
    std::vector<TriVertex> vertices;
    std::vector<unsigned int> indices;

    void clear();
};
