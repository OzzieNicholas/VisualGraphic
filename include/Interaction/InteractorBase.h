/*
 * InteractorBase.h��������Ϊ���ࣨ����ӿڣ�
 *
 * ���ܸ�����
 *  - �ṩ���н�����Ϊ���ͳһ�ӿڶ���
 *  - ���������¼���Ӧ����ꡢ���̡����֣����
 *  - ��������������ϵ�ĳ�����֧࣬����չ��ģʽ�л�
 *
 * ʹ�ó�����
 *  - InteractionManager ���¼�ί�ж���
 *  - ������ʵ���ض�������Ϊ�����ӽǿ��ơ�����㡢�༭���εȣ�
 *  - �� InteractorHost �ӿ�Эͬ��Ӧ�û�����
 */

#pragma once

#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

class InteractorHost;

class InteractorBase {
public:
    virtual ~InteractorBase();

    // ========== �������¼� ========== //
    virtual void onMousePress(QMouseEvent* event, InteractorHost* host) = 0;
    virtual void onMouseMove(QMouseEvent* event, InteractorHost* host) = 0;
    virtual void onWheel(QWheelEvent* event, InteractorHost* host) = 0;
    virtual void onKeyPress(QKeyEvent* event, InteractorHost* host) = 0;
};
