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

class InteractorBase;
class QMouseEvent;
class QWheelEvent;
class QKeyEvent;
class InteractorHost; // 抽象控件接口

// ========== 交互控制器类定义 ========== //
class InteractorManager {
public:
    InteractorManager();
    ~InteractorManager();

    // ========== 事件转发 ========== //

    // 鼠标按下
    void onMousePress(QMouseEvent* event, InteractorHost* host);

    // 鼠标移动
    void onMouseMove(QMouseEvent* event, InteractorHost* host);

    // 滚轮滚动
    void onWheel(QWheelEvent* event, InteractorHost* host);

    // 键盘按键
    void onKeyPress(QKeyEvent* event, InteractorHost* host);

    // ========== 交互器管理 ========== //

    // 设置当前激活交互器
    void setActiveInteractor(std::shared_ptr<InteractorBase> interactor);

    // 获取当前激活交互器
    std::shared_ptr<InteractorBase> getActiveInteractor() const;

    // 清除当前交互器
    void clearInteractor();

private:
    std::shared_ptr<InteractorBase> m_activeInteractor; // 当前激活交互器
};
