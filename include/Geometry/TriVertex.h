// TriVertex.h
// ����һ���������񶥵�ṹ������λ�á����ߺ���ɫ

#pragma once

#include <vector>

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

#include <QVector3D>

struct TriVertex {
    QVector3D position;
    QVector3D normal;
    QVector3D color;
};
