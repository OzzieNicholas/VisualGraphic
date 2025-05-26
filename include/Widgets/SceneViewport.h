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

#include "../Geometry/MeshTri.h"
#include "../Geometry/MeshLine.h"
#include "../Geometry/MeshTriBuilder.h"
#include "../Geometry/MeshLineBuilder.h"

#include "../Renderer/MeshTriRenderer.h"
#include "../Renderer/MeshLineRenderer.h"

#include "../Interaction/InteractorManager.h"
#include "../Interaction/InteractorHost.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

class SceneViewport : public QOpenGLWidget, public InteractorHost, protected QOpenGLFunctions {
    Q_OBJECT

public:
    // ========== ���������� ========== //

    explicit SceneViewport(QWidget* parent = nullptr);
    ~SceneViewport();

    // ========== ��Ⱦ�����ӿ� ========== //

    // �����������񣨹�������ʹ�ã�
    void setPolylineMesh(const MeshLine& mesh);

    // �����������
    void clearPolyline();

    // ========== InteractorHost �ӿ�ʵ�� ========== //

    QMatrix4x4 getViewMatrix() const override;
    QMatrix4x4 getProjectionMatrix() const override;
    QSize getViewportSize() const override;
    void requestViewportUpdate() override;
    float getCameraZoom() const override;

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

    MeshTri m_groundMesh; // ��������
    MeshLine m_polylineMesh; // ���߹��ɵ������߶�
    MeshLine m_axisLineMesh; // �������߶�

    MeshTriRenderer m_groundRenderer;   // ����������Ⱦ��
    MeshLineRenderer m_polylineRenderer; // ����������Ⱦ��
    MeshLineRenderer m_axisRenderer;    // ��������Ⱦ��

    QOpenGLShaderProgram* m_shaderProgram = nullptr; // ��ɫ��

    // ========== ������Ʋ��� ========== //

    float m_rotationX = 45.0f;  // �� X �����ת�Ƕ�
    float m_rotationY = -45.0f; // �� Y �����ת�Ƕ�
    float m_zoom = 20.0f;       // �������ӣ��Ӿࣩ
    float m_panX = 0.0f;        // ˮƽƽ����
    float m_panY = 0.0f;        // ��ֱƽ����
    QPoint m_lastMousePos;      // ��һ�����λ��

    // ========== ������ ========== //

    InteractorManager* m_interactorManager = nullptr;

    // ========== �ڲ��������������Խ׶Σ���������������� ========== //

    QVector3D mapClickToPlane(float screenX, float screenY);  // ��Ǩ�� InteractorUtils

};
