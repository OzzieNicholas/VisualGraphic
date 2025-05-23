/*
 * LineMeshRenderer.h���߶�������Ⱦ��
 *
 * ���ܸ�����
 *  - �� LineMesh �еĶ�������������ϴ��� GPU
 *  - ���� OpenGL �������VAO/VBO/EBO��
 *  - ʹ��ָ����ɫ�������߶�ͼԪ
 *
 * ʹ�ó�����
 *  - ��Ⱦ��������ģ��
 *  - չʾ���潨ģ�����ա�����Ч���ȿ��ӻ����
 *  - ͼ��ѧ��ѧ���㷨��ʾƽ̨�е�������ͼԪ��Ⱦ����
 */

#pragma once

#include "../Geometry/LineMesh.h"

#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

class LineMeshRenderer {
public:
    // ========== ���������� ========== //

    LineMeshRenderer();
    ~LineMeshRenderer();

    // ========== �����ϴ�����Ⱦ ========== //

    // �����߶�����
    void setMesh(const LineMesh& mesh);

    // �����߶�����
    void renderMesh(QOpenGLShaderProgram* program);

private:
    QOpenGLVertexArrayObject m_meshVAO;   // �����������
    QOpenGLBuffer m_meshVBO;              // ���㻺�����
    QOpenGLBuffer m_meshEBO;              // �����������

    int m_meshIndexCount = 0;             // ������
    bool m_meshInitialized = false;       // �Ƿ��ѳ�ʼ��
    GLenum m_meshDrawMode = GL_LINES;     // ͼԪ����
};
