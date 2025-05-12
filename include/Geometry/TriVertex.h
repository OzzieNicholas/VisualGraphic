// TriVertex.h
// 定义一个三角网格顶点结构，包括位置、法线和颜色

#pragma once

#include <QVector3D>

struct TriVertex {
    QVector3D position;
    QVector3D normal;
    QVector3D color;
};
