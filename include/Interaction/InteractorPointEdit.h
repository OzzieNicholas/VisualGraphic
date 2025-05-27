/*
 * InteractorPointEdit.h：用户点编辑交互器
 *
 * 功能概述：
 *  - 支持对一组空间点进行交互式选择与移动
 *  - 鼠标点击选点、按住拖动修改点位置
 *  - 支持 ESC 取消当前选中状态
 *  - 提供可配置的拾取容差（像素单位）
 *
 * 使用场景：
 *  - 编辑 NURBS、Bezier 控制点
 *  - 算法调试中动态调整初始数据
 *  - 教学演示中直观可视地修改构造元素
 */

#pragma once

#include "./InteractorBase.h"
#include <vector>
#include <QVector3D>
#include <QPoint>

class InteractorPointEdit : public InteractorBase {
public:
    InteractorPointEdit();
    ~InteractorPointEdit() override;

    // ========== 鼠标键盘事件 ========== //
    void onMousePress(QMouseEvent* event, InteractorHost* host) override;
    void onMouseMove(QMouseEvent* event, InteractorHost* host) override;
    void onWheel(QWheelEvent* event, InteractorHost* host) override;
    void onKeyPress(QKeyEvent* event, InteractorHost* host) override;

	// ========== 点编辑操作 ========== //

    // 设置待编辑的点引用
    void setTargetPoints(std::vector<QVector3D>* points);

    // 设置拾取半径（屏幕像素）
    void setPickRadius(float radius);

private:
    std::vector<QVector3D>* m_pointsRef = nullptr; // 编辑目标（外部数据）
    int m_selectedIndex = -1;                      // 当前选中点
    float m_pickRadius = 8.0f;                     // 拾取容差
    QPoint m_lastMousePos;                         // 上次鼠标位置
};
