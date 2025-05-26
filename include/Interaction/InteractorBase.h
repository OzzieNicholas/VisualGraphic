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
 *  - �� SceneViewport Эͬ��Ӧ�û��������
 */

#pragma once

#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

class SceneViewport;

// ========== ������Ϊ����ӿ� ========== //
class InteractorBase {
public:
    virtual ~InteractorBase();

    // ========== ����¼��ӿ� ========== //

    // ��갴��
    virtual void onMousePress(QMouseEvent* event, SceneViewport* viewport) = 0;

    // ����ƶ�
    virtual void onMouseMove(QMouseEvent* event, SceneViewport* viewport) = 0;

    // ������
    virtual void onWheel(QWheelEvent* event, SceneViewport* viewport) = 0;

    // ========== �����¼��ӿ� ========== //

    // ���̰���
    virtual void onKeyPress(QKeyEvent* event, SceneViewport* viewport) = 0;
};
