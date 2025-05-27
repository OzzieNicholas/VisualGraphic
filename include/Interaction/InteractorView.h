/*
 * InteractorView.h���ӽǿ��ƽ�����
 *
 * ���ܸ�����
 *  - �����û�������룬ʵ����ͼ����ת�����š�ƽ�Ʋ���
 *  - ����Ŀ���� InteractorHost �ṩ������ SceneViewport��
 *
 * ʹ�ó�����
 *  - ��άģ�Ͳ鿴�����γ���������ת
 *  - HMI ���ӻ����������ڵ����۲��ӽ�
 */

#pragma once

#include "./InteractorBase.h"
#include <QPoint>

class InteractorView : public InteractorBase {
public:
    InteractorView();
    ~InteractorView() override;

    // ����¼�
    void onMousePress(QMouseEvent* event, InteractorHost* host) override;
    void onMouseMove(QMouseEvent* event, InteractorHost* host) override;
    void onWheel(QWheelEvent* event, InteractorHost* host) override;

    // �����¼�
    void onKeyPress(QKeyEvent* event, InteractorHost* host) override;

private:
    QPoint m_lastMousePos; // �ϴ����λ��
};
