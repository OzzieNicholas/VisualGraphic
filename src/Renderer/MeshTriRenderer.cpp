#include "../../include/Renderer/MeshTriRenderer.h"

// ========== ���������� ========== //

MeshTriRenderer::MeshTriRenderer()
    : m_meshVBO(QOpenGLBuffer::VertexBuffer),
    m_meshEBO(QOpenGLBuffer::IndexBuffer) {
}

MeshTriRenderer::~MeshTriRenderer() {
    m_meshVAO.destroy();
    m_meshVBO.destroy();
    m_meshEBO.destroy();
}

// ========== �����ϴ�����Ⱦ ========== //

// ��������
void MeshTriRenderer::setMesh(const MeshTri& mesh) {
    if (!m_meshInitialized) {
        m_meshVAO.create();
        m_meshVBO.create();
        m_meshEBO.create();
        m_meshInitialized = true;
    }

    m_meshVAO.bind();

	// ���㻺��
    m_meshVBO.bind();
    m_meshVBO.allocate(mesh.getVertices().data(), int(mesh.getVertices().size() * sizeof(MeshVertex)));

	// ��������
    m_meshEBO.bind();
    m_meshEBO.allocate(mesh.getIndices().data(), int(mesh.getIndices().size() * sizeof(unsigned int)));

    // ���԰�
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

	// ��ȡ������
    m_meshIndexCount = int(mesh.getIndices().size());
	
	// ���û���ģʽ
    switch (mesh.getDrawPrimitiveType()) {
        case DrawPrimitiveType::Triangles:
            m_meshDrawMode = GL_TRIANGLES;
            break;
        case DrawPrimitiveType::Lines:
            m_meshDrawMode = GL_LINES;
            break;
        case DrawPrimitiveType::Points:
            m_meshDrawMode = GL_POINTS;
            break;
        case DrawPrimitiveType::Quads:
            m_meshDrawMode = GL_QUADS;
            break;
        default:
            m_meshDrawMode = GL_TRIANGLES;
            break;
    }
}

// ��������
void MeshTriRenderer::renderMesh(QOpenGLShaderProgram* program) {
    if (!m_meshInitialized || m_meshIndexCount == 0) {
        return;
    }
    program->bind();
    m_meshVAO.bind();
    glDrawElements(m_meshDrawMode, m_meshIndexCount, GL_UNSIGNED_INT, nullptr);
    m_meshVAO.release();
    program->release();
}
