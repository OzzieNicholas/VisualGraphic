/*
 * InteractorHost.h�������ؼ������ӿ�
 *
 * ���ܸ�����
 *  - �������н�����Ϊ����Ŀؼ����ݽӿ�
 *  - �ṩͶӰ/��ͼ���󡢳ߴ硢����ͶӰ��
 *  - ���ڽ�������InteractorBase�����ʿؼ�������
 *
 * ʹ�ó�����
 *  - �� Widget �������ɽ����ؼ�ʵ��
 *  - ������ InteractorXxx ����ʿؼ�״̬
 */

#pragma once

#include <QMatrix4x4>
#include <QSize>

class InteractorHost {
public:
    virtual ~InteractorHost() = default;

    // ========== �ؼ������ӿ� ========== //

    // ��ȡ��ͼ����
    virtual QMatrix4x4 getViewMatrix() const = 0;

    // ��ȡͶӰ����
    virtual QMatrix4x4 getProjectionMatrix() const = 0;

    // ��ȡ�ؼ��ߴ磨���أ�
    virtual QSize getViewportSize() const = 0;

    // ����ؼ����£��ػ棩
    virtual void requestViewportUpdate() = 0;

    // ��ȡ������ Z=0 ƽ��ĵ�ӳ�丨��
    virtual float getCameraZoom() const = 0;
};
