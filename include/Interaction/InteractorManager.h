/*
 * InteractorManager.h：交互控制器（事件分发与模式切换中心）
 *
 * 功能概述：
 *  - 管理并维护当前激活的交互器（InteractorBase 派生类）
 *  - 提供统一的事件转发入口（鼠标、键盘、滚轮）
 *  - 支持设置、获取、清除当前交互器
 *
 * 使用场景：
 *  - 控件（如 SceneViewport）接收到事件后，将其统一转发给本类处理
 *  - 动态切换交互模式（如视角、点选、绘制等）
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

    // ========== 鼠标键盘事件 ========== //

    void onMousePress(QMouseEvent* event, InteractorHost* host);
    void onMouseMove(QMouseEvent* event, InteractorHost* host);
    void onWheel(QWheelEvent* event, InteractorHost* host);
    void onKeyPress(QKeyEvent* event, InteractorHost* host);

    // ========== 交互器管理 ========== //

    // 设置交互器
    void setActiveInteractor(std::shared_ptr<InteractorBase> interactor);

    // 获取交互器
    std::shared_ptr<InteractorBase> getActiveInteractor() const;

    // 判断是否存在交互器
    bool hasActiveInteractor() const;

    // 重置交互器
    template<typename T>
    void resetIf() {
        if (std::dynamic_pointer_cast<T>(m_activeInteractor)) {
            m_activeInteractor.reset();
        }
    }

    // 清除交互器
    void clearActiveInteractor();

private:
    std::shared_ptr<InteractorBase> m_activeInteractor; // 交互器
};
