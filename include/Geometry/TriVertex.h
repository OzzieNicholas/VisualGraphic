// TriVertex.h
// 定义一个三角网格顶点结构，包括位置、法线和颜色

#pragma once

#include <vector>

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>

#include <QMouseEvent>
#include <QVector3D>

struct TriVertex {
    QVector3D position;
    QVector3D normal;
    QVector3D color;
};
