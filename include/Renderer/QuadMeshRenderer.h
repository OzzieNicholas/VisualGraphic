/*
 * QuadMeshRenderer.h���ı���������Ⱦ��
 *
 * ���ܸ�����
 *  - �� QuadMesh ���������������ϴ��� GPU
 *  - ���� VAO/VBO/EBO �������
 *  - ʹ��ָ����ɫ�������ı���ͼԪ����
 *
 * ʹ�ó�����
 *  - ��Ⱦƽ��ṹ������桢ǽ�塢�������棩
 *  - ���ӻ������ı���Ľ�ģ���
 *  - ������ɢ����������ͼ���ͼ�νṹչʾ
 */

#pragma once

#include "../Geometry/QuadMesh.h"

#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

class QuadMeshRenderer {
public:
    // ========== ���������� ========== //

    QuadMeshRenderer();
    ~QuadMeshRenderer();

    // ========== �����ϴ�����Ⱦ ========== //

    // ��������
    void setMesh(const QuadMesh& mesh);

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
