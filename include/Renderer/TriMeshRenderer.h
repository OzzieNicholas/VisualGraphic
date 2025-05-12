// TriMeshRenderer.h
// 渲染 TriMesh 的类：将顶点数据上传到 OpenGL 并负责绘制

#pragma once
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

#include "../Geometry/TriMesh.h"

class TriMeshRenderer {
public:
    TriMeshRenderer();
    ~TriMeshRenderer();

    void setMesh(const TriMesh& mesh);
    void drawMesh(QOpenGLShaderProgram* program);

private:
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ebo;

    int indexCount = 0;
    bool initialized = false;
};
