/*
 * InteractorBase.h：交互行为基类（抽象接口）
 *
 * 功能概述：
 *  - 提供所有交互行为类的统一接口定义
 *  - 定义输入事件响应（鼠标、键盘、滚轮）入口
 *  - 用作交互策略体系的抽象基类，支持扩展与模式切换
 *
 * 使用场景：
 *  - InteractionManager 的事件委托对象
 *  - 派生类实现特定交互行为（如视角控制、构造点、编辑几何等）
 *  - 与 InteractorHost 接口协同响应用户操作
 */

#pragma once

#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

class InteractorHost;

class InteractorBase {
public:
    virtual ~InteractorBase();

    // ========== 鼠标键盘事件 ========== //
    virtual void onMousePress(QMouseEvent* event, InteractorHost* host) = 0;
    virtual void onMouseMove(QMouseEvent* event, InteractorHost* host) = 0;
    virtual void onWheel(QWheelEvent* event, InteractorHost* host) = 0;
    virtual void onKeyPress(QKeyEvent* event, InteractorHost* host) = 0;
};
