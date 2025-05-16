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
    vbo.allocate(mesh.getVertices().data(), int(mesh.getVertices().size() * sizeof(MeshVertex)));

    ebo.bind();
    ebo.allocate(mesh.getIndices().data(), int(mesh.getIndices().size() * sizeof(unsigned int)));

    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, position));
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, normal));
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, color));
    f->glEnableVertexAttribArray(2);

    vao.release();
    vbo.release();
    ebo.release();

    indexCount = int(mesh.getIndices().size());
	
    switch (mesh.getDrawType()) {
        case DrawPrimitiveType::Triangles:
            drawMode = GL_TRIANGLES;
            break;
        case DrawPrimitiveType::Lines:
            drawMode = GL_LINES;
            break;
        case DrawPrimitiveType::Points:
            drawMode = GL_POINTS;
            break;
        case DrawPrimitiveType::Quads:
            drawMode = GL_QUADS;
            break;
        default:
            drawMode = GL_TRIANGLES;
            break;
    }
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
