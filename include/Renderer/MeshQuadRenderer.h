/*
 * MeshQuadRenderer.h���ı���������Ⱦ��
 *
 * ���ܸ�����
 *  - �� MeshQuad ���������������ϴ��� GPU
 *  - ���� VAO/VBO/EBO �������
 *  - ʹ��ָ����ɫ�������ı���ͼԪ����
 *
 * ʹ�ó�����
 *  - ��Ⱦƽ��ṹ������桢ǽ�塢�������棩
 *  - ���ӻ������ı���Ľ�ģ���
 *  - ������ɢ����������ͼ���ͼ�νṹչʾ
 */

#pragma once

#include "../Geometry/MeshQuad.h"

#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

class MeshQuadRenderer {
public:
    // ========== ���������� ========== //

    MeshQuadRenderer();
    ~MeshQuadRenderer();

    // ========== �����ϴ�����Ⱦ ========== //

    // ��������
    void setMesh(const MeshQuad& mesh);

    // ��������
    void renderMesh(QOpenGLShaderProgram* program);

private:
    QOpenGLVertexArrayObject m_meshVAO;   // �����������
    QOpenGLBuffer m_meshVBO;              // ���㻺�����
    QOpenGLBuffer m_meshEBO;              // �����������

    int m_meshIndexCount = 0;             // ������
    bool m_meshInitialized = false;       // �Ƿ��ѳ�ʼ��
    GLenum m_meshDrawMode = GL_QUADS;     // ͼԪ����
};
