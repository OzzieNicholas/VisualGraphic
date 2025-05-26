/*
 * MeshTriRenderer.h������������Ⱦ��
 *
 * ���ܸ�����
 *  - �� MeshTri ����/���������ϴ��� GPU
 *  - �󶨲����� VAO/VBO/EBO
 *  - ʹ��ָ����ɫ�����������Ⱦ
 *
 * ʹ�ó�����
 *  - ��Ⱦ�����߶Ρ������ᡢ·�����ߵȸ���ͼԪ
 *  - ���ӻ����α߽硢���Խṹ����
 *  - ͼ��ϵͳ�з���״ͼԪ�Ŀ�����Ⱦ
 */

#pragma once

#include "../Geometry/MeshTri.h"

#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

class MeshTriRenderer {
public:
    // ========== ���������� ========== //

    MeshTriRenderer();
    ~MeshTriRenderer();

    // ========== �����ϴ�����Ⱦ ========== //

    // ��������
    void setMesh(const MeshTri& mesh);

    // ��������
    void renderMesh(QOpenGLShaderProgram* program);

private:
    QOpenGLVertexArrayObject m_meshVAO;   // �����������
    QOpenGLBuffer m_meshVBO;              // ���㻺�����
    QOpenGLBuffer m_meshEBO;              // �����������

    int m_meshIndexCount = 0;             // ������
    bool m_meshInitialized = false;       // �Ƿ��ѳ�ʼ��
    GLenum m_meshDrawMode = GL_TRIANGLES; // ͼԪ����
};
