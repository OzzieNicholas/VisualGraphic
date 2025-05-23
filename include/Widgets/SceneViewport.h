/*
 * SceneViewport.h����ά������ͼ���ڣ�����Ⱦ�ؼ���
 *
 * ���ܸ�����
 *  - �ṩ���� OpenGL �Ľ���ʽ��ά���ӻ�����
 *  - ������Ⱦ��������������ᡢ���桢���ߵȣ�
 *  - ֧���ӽ���ת�����š�ƽ�ƵȽ�������
 *  - ֧�ֵ��ʰȡ��������ߵ���û�����
 *
 * ʹ�ó�����
 *  - �������ݺ�ͼ���㷨�Ķ�̬չʾ
 *  - ͼ��ѧ��ѧ��HMI ���ӻ��뽻��ʵ��
 */

#pragma once

#include "../Geometry/TriMesh.h"
#include "../Geometry/LineMesh.h"
#include "../Geometry/TriMeshBuilder.h"
#include "../Geometry/LineMeshBuilder.h"

#include "../Renderer/TriMeshRenderer.h"
#include "../Renderer/LineMeshRenderer.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

class SceneViewport : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    // ========== ���������� ========== //

    explicit SceneViewport(QWidget* parent = nullptr);
    ~SceneViewport();

protected:
    // ========== Qt �¼����� ========== //

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    // ========== ��Ⱦ��Դ ========== //

    TriMesh m_groundMesh; // ��������
    LineMesh m_polylineMesh; // ���߹��ɵ������߶�
    LineMesh m_axisLineMesh; // �������߶�

    TriMeshRenderer m_groundRenderer;   // ����������Ⱦ��
    LineMeshRenderer m_polylineRenderer; // ����������Ⱦ��
    LineMeshRenderer m_axisRenderer;    // ��������Ⱦ��

    QOpenGLShaderProgram* m_shaderProgram = nullptr; // ��ɫ��

    // ========== ������Ʋ��� ========== //

    float m_rotationX = 45.0f;  // �� X �����ת�Ƕ�
    float m_rotationY = -45.0f; // �� Y �����ת�Ƕ�
    float m_zoom = 20.0f;       // �������ӣ��Ӿࣩ
    float m_panX = 0.0f;        // ˮƽƽ����
    float m_panY = 0.0f;        // ��ֱƽ����
    QPoint m_lastMousePos;      // ��һ�����λ��

    // ========== ����״̬ ========== //

    std::vector<QVector3D> m_polylinePoints; // �����ӵ����ߵ�

    // ========== �ڲ����� ========== //

	// ����Ļ����ת��Ϊ��������
    QVector3D mapClickToPlane(float screenX, float screenY);

	// ������������
    void updatePolylineMesh();

	// �����������
    void clearPolyline();
};
