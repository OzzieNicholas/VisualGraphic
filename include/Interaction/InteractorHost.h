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

    // ��ȡ�ؼ��ߴ磨���أ�
    virtual QSize getViewportSize() const = 0;

    // ����ؼ����£��ػ棩
    virtual void requestViewportUpdate() = 0;

    // ��ȡ������루��������ȵ�����
    virtual float getCameraZoom() const = 0;

    // ========== �ӽǲ��� ========== //

    // ��ת�ӽǣ��� X��Y��
    virtual void rotateView(float deltaX, float deltaY) = 0;

    // ƽ���ӽǣ�ƽ��ƽ��Ϊ��Ļƽ�棩
    virtual void panView(float offsetX, float offsetY) = 0;

    // �����ӽǣ�ͨ�����������ƣ�
    virtual void zoomView(float zoomDelta) = 0;
};
