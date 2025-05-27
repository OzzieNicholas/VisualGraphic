/*
 * InteractorPointInput.h：用户点输入交互器
 *
 * 功能概述：
 *  - 通过鼠标点击采集用户输入的空间点
 *  - 支持实时可视化反馈（如辅助折线预览）
 *  - 支持 ESC 清除当前所有输入点
 *  - 提供接口供其他模块（如算法构造器）访问输入点数据
 *
 * 使用场景：
 *  - 用于绘制折线、Bezier 控制点、NURBS 控制网格等曲线/曲面输入
 *  - 作为几何构造、交互算法测试的前置数据来源
 *  - 可与 PointEdit / ObjectPick 等交互器联合使用
 */

#pragma once

#include "./InteractorBase.h"
#include <vector>
#include <QVector3D>

class InteractorPointInput : public InteractorBase {
public:
    InteractorPointInput();
    ~InteractorPointInput() override;

    // ========== 鼠标键盘事件 ========== //
    void onMousePress(QMouseEvent* event, InteractorHost* host) override;
    void onMouseMove(QMouseEvent* event, InteractorHost* host) override;
    void onWheel(QWheelEvent* event, InteractorHost* host) override;
    void onKeyPress(QKeyEvent* event, InteractorHost* host) override;

    // ========== 输入点的处理 ========== //

    // 获取输入点
    const std::vector<QVector3D>& getInputPoints() const;

    // 清空输入点
    void clearInputPoints();

private:
    std::vector<QVector3D> m_inputPoints; // 输入点集
};
