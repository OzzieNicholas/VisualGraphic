#include "../../include/Renderer/MeshLineRenderer.h"

// ========== 构造与析构 ========== //

MeshLineRenderer::MeshLineRenderer()
    : m_meshVBO(QOpenGLBuffer::VertexBuffer),
    m_meshEBO(QOpenGLBuffer::IndexBuffer) {
}

MeshLineRenderer::~MeshLineRenderer() {
    m_meshVAO.destroy();
    m_meshVBO.destroy();
    m_meshEBO.destroy();
}

// ========== 数据上传与渲染 ========== //

// 设置线段网格
void MeshLineRenderer::setMesh(const MeshLine& mesh) {
    if (!m_meshInitialized) {
        m_meshVAO.create();
        m_meshVBO.create();
        m_meshEBO.create();
        m_meshInitialized = true;
    }

    m_meshVAO.bind();

    m_meshVBO.bind();
    m_meshVBO.allocate(mesh.getVertices().data(), int(mesh.getVertices().size() * sizeof(MeshVertex)));

    m_meshEBO.bind();
    m_meshEBO.allocate(mesh.getIndices().data(), int(mesh.getIndices().size() * sizeof(uint)));

    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, position));
    f->glEnableVertexAttribArray(0);

    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, color));
    f->glEnableVertexAttribArray(1);

    m_meshVAO.release();
    m_meshVBO.release();
    m_meshEBO.release();

    m_meshIndexCount = int(mesh.getIndices().size());
    m_meshDrawMode = GL_LINES;
}

// 绘制线段网格
void MeshLineRenderer::renderMesh(QOpenGLShaderProgram* program) {
    if (!m_meshInitialized || m_meshIndexCount == 0) {
        return;
    }

    program->bind();
    m_meshVAO.bind();
    glDrawElements(m_meshDrawMode, m_meshIndexCount, GL_UNSIGNED_INT, nullptr);
    m_meshVAO.release();
    program->release();
}
