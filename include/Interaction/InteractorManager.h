/*
 * InteractorManager.h���������������¼��ַ���ģʽ�л����ģ�
 *
 * ���ܸ�����
 *  - ����ά����ǰ����Ľ�������InteractorBase �����ࣩ
 *  - �ṩͳһ���¼�ת����ڣ���ꡢ���̡����֣�
 *  - ֧�����á���ȡ�������ǰ������
 *
 * ʹ�ó�����
 *  - �ؼ����� SceneViewport�����յ��¼��󣬽���ͳһת�������ദ��
 *  - ��̬�л�����ģʽ�����ӽǡ���ѡ�����Ƶȣ�
 */

#pragma once

#include <memory>

class InteractorBase;
class QMouseEvent;
class QWheelEvent;
class QKeyEvent;
class InteractorHost; // ����ؼ��ӿ�

// ========== �����������ඨ�� ========== //
class InteractorManager {
public:
    InteractorManager();
    ~InteractorManager();

    // ========== �¼�ת�� ========== //

    // ��갴��
    void onMousePress(QMouseEvent* event, InteractorHost* host);

    // ����ƶ�
    void onMouseMove(QMouseEvent* event, InteractorHost* host);

    // ���ֹ���
    void onWheel(QWheelEvent* event, InteractorHost* host);

    // ���̰���
    void onKeyPress(QKeyEvent* event, InteractorHost* host);

    // ========== ���������� ========== //

    // ���õ�ǰ�������
    void setActiveInteractor(std::shared_ptr<InteractorBase> interactor);

    // ��ȡ��ǰ�������
    std::shared_ptr<InteractorBase> getActiveInteractor() const;

    // �����ǰ������
    void clearInteractor();

private:
    std::shared_ptr<InteractorBase> m_activeInteractor; // ��ǰ�������
};
