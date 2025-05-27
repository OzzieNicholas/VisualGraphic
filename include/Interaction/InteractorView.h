/*
 * InteractorView.h：视角控制交互器
 *
 * 功能概述：
 *  - 处理用户鼠标输入，实现视图的旋转、缩放、平移操作
 *  - 操作目标由 InteractorHost 提供（例如 SceneViewport）
 *
 * 使用场景：
 *  - 三维模型查看、几何场景交互旋转
 *  - HMI 可视化界面中用于调整观察视角
 */

#pragma once

#include "./InteractorBase.h"
#include <QPoint>

class InteractorView : public InteractorBase {
public:
    InteractorView();
    ~InteractorView() override;

    // 鼠标事件
    void onMousePress(QMouseEvent* event, InteractorHost* host) override;
    void onMouseMove(QMouseEvent* event, InteractorHost* host) override;
    void onWheel(QWheelEvent* event, InteractorHost* host) override;

    // 键盘事件
    void onKeyPress(QKeyEvent* event, InteractorHost* host) override;

private:
    QPoint m_lastMousePos; // 上次鼠标位置
};
