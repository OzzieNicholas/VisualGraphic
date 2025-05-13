// TriMeshRenderer.h
// ��Ⱦ TriMesh ���ࣺ�����������ϴ��� OpenGL ���������

#pragma once

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
	GLenum drawMode = GL_TRIANGLES;
};
