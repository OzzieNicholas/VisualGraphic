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

class QMouseEvent;
class QWheelEvent;
class QKeyEvent;

class InteractorBase;
class InteractorHost;

class InteractorManager {
public:
    InteractorManager();
    ~InteractorManager();

    // ========== �������¼� ========== //

    void onMousePress(QMouseEvent* event, InteractorHost* host);
    void onMouseMove(QMouseEvent* event, InteractorHost* host);
    void onWheel(QWheelEvent* event, InteractorHost* host);
    void onKeyPress(QKeyEvent* event, InteractorHost* host);

    // ========== ���������� ========== //

    // ���ý�����
    void setActiveInteractor(std::shared_ptr<InteractorBase> interactor);

    // ��ȡ������
    std::shared_ptr<InteractorBase> getActiveInteractor() const;

    // �ж��Ƿ���ڽ�����
    bool hasActiveInteractor() const;

    // ���ý�����
    template<typename T>
    void resetIf() {
        if (std::dynamic_pointer_cast<T>(m_activeInteractor)) {
            m_activeInteractor.reset();
        }
    }

    // ���������
    void clearActiveInteractor();

private:
    std::shared_ptr<InteractorBase> m_activeInteractor; // ������
};
