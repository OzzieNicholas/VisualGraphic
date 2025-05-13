// TriMeshRenderer.cpp
// 实现 TriMeshRenderer，负责上传 VAO/VBO 并绘制

#include "../../include/Renderer/TriMeshRenderer.h"

TriMeshRenderer::TriMeshRenderer()
    : vbo(QOpenGLBuffer::VertexBuffer),
    ebo(QOpenGLBuffer::IndexBuffer) {
}

TriMeshRenderer::~TriMeshRenderer() {
    vao.destroy();
    vbo.destroy();
    ebo.destroy();
}

void TriMeshRenderer::setMesh(const TriMesh& mesh) {
    if (!initialized) {
        vao.create();
        vbo.create();
        ebo.create();
        initialized = true;
    }

    vao.bind();

    vbo.bind();
    vbo.allocate(mesh.vertices.data(), int(mesh.vertices.size() * sizeof(TriVertex)));

    ebo.bind();
    ebo.allocate(mesh.indices.data(), int(mesh.indices.size() * sizeof(unsigned int)));

    // 假设 layout(location = 0) 为 position
    //         layout(location = 1) 为 normal
    //         layout(location = 2) 为 color
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TriVertex), (void*)offsetof(TriVertex, position));
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TriVertex), (void*)offsetof(TriVertex, normal));
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(TriVertex), (void*)offsetof(TriVertex, color));
    f->glEnableVertexAttribArray(2);

    vao.release();
    vbo.release();
    ebo.release();

    indexCount = int(mesh.indices.size());
	drawMode = mesh.primitiveType;
}

void TriMeshRenderer::drawMesh(QOpenGLShaderProgram* program) {
    if (!initialized || indexCount == 0) {
        return;
    }
    program->bind();
    vao.bind();
    glDrawElements(drawMode, indexCount, GL_UNSIGNED_INT, nullptr);
    vao.release();
    program->release();
}
