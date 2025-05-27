/*
 * InteractorHost.h�������ؼ������ӿ�
 *
 * ���ܸ�����
 *  - �������н�����Ϊ����Ŀؼ����ݽӿ�
 *  - �ṩͶӰ/��ͼ���󡢳ߴ硢����ͶӰ��
 *  - �ṩ�ӽǲ����ӿڣ���ת��ƽ�ơ����ţ�
 *
 * ʹ�ó�����
 *  - �� Widget �������ɽ����ؼ�ʵ��
 *  - ������ InteractorXxx ����ʿؼ�״̬
 *  - �� InteractorView Эͬ���ڳ�����������
 */

#pragma once

#include "../Geometry/MeshLine.h"
#include <QMatrix4x4>
#include <QSize>

class InteractorHost {
public:
    virtual ~InteractorHost() = default;

    // ========== �ؼ����� ========== //

    // ��ȡ��ͼ����
    virtual QMatrix4x4 getViewMatrix() const = 0;

    // ��ȡͶӰ����
    virtual QMatrix4x4 getProjectionMatrix() const = 0;

    // ��ȡ�ؼ��ߴ�
    virtual QSize getViewportSize() const = 0;

    // ����ؼ�����
    virtual void requestViewportUpdate() = 0;

    // ��ȡ�������
    virtual float getCameraZoom() const = 0;

    // ========== �ӽǲ��� ========== //

    // ��ת�ӽǣ��� X��Y��
    virtual void rotateView(float deltaX, float deltaY) = 0;

    // ƽ���ӽǣ�ƽ��ƽ��Ϊ��Ļƽ�棩
    virtual void panView(float offsetX, float offsetY) = 0;

    // �����ӽǣ�ͨ�����������ƣ�
    virtual void zoomView(float zoomDelta) = 0;

    // ========== Ԥ������ ========== //

    // ��������
    virtual void setPolylineMesh(const MeshLine& mesh) = 0;

    // �������
    virtual void clearPolyline() = 0;
};
