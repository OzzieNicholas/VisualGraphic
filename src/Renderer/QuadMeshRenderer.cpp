#include "../../include/Renderer/QuadMeshRenderer.h"

// ========== 构造与析构 ========== //

QuadMeshRenderer::QuadMeshRenderer()
    : m_meshVBO(QOpenGLBuffer::VertexBuffer),
    m_meshEBO(QOpenGLBuffer::IndexBuffer) {
}

QuadMeshRenderer::~QuadMeshRenderer() {
    m_meshVAO.destroy();
    m_meshVBO.destroy();
    m_meshEBO.destroy();
}

// ========== 数据上传与渲染 ========== //

// 设置网格
void QuadMeshRenderer::setMesh(const QuadMesh& mesh) {
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

    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, normal));
    f->glEnableVertexAttribArray(1);

    f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, color));
    f->glEnableVertexAttribArray(2);

    m_meshVAO.release();
    m_meshVBO.release();
    m_meshEBO.release();

    m_meshIndexCount = int(mesh.getIndices().size());
    m_meshDrawMode = GL_QUADS;  // 固定为四边形
}

// 绘制网格
void QuadMeshRenderer::renderMesh(QOpenGLShaderProgram* program) {
    if (!m_meshInitialized || m_meshIndexCount == 0) {
        return;
    }

    program->bind();
    m_meshVAO.bind();
    glDrawElements(m_meshDrawMode, m_meshIndexCount, GL_UNSIGNED_INT, nullptr);
    m_meshVAO.release();
    program->release();
}
