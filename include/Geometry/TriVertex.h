// TriVertex.h
// ����һ���������񶥵�ṹ������λ�á����ߺ���ɫ

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
