/*
 * InteractorObjectSelect.h：对象选择交互器
 *
 * 功能概述：
 *  - 用户通过鼠标点击选中场景中的对象
 *  - 基于对象中心点与点击位置的投影距离判断选择
 *  - 提供选中状态查询、清除等接口
 *
 * 使用场景：
 *  - HMI 控件选择、模型组件选择
 *  - 后续几何编辑、属性面板显示的入口交互
 *  - 算法调试时用于指定目标对象
 */

#pragma once

#include "./InteractorBase.h"
#include <vector>
#include <QVector3D>
#include <QPoint>

class InteractorObjectSelect : public InteractorBase {
public:
    InteractorObjectSelect();
    ~InteractorObjectSelect() override;

    // ========== 鼠标键盘事件 ========== //
    void onMousePress(QMouseEvent* event, InteractorHost* host) override;
    void onMouseMove(QMouseEvent* event, InteractorHost* host) override;
    void onWheel(QWheelEvent* event, InteractorHost* host) override;
    void onKeyPress(QKeyEvent* event, InteractorHost* host) override;

	// ========== 选择对象 ========== //

    // 设置可选择对象的空间位置
    void setSelectableCenters(const std::vector<QVector3D>* centers);

    // 设置拾取容差
    void setPickRadius(float radius);

    // 获取当前选中对象索引（-1 表示无选中）
    int getSelectedIndex() const;

    // 清除当前选中状态
    void clearSelection();

private:
    const std::vector<QVector3D>* m_centersRef = nullptr; // 选择目标中心点
    float m_pickRadius = 8.0f; // 拾取容差
    int m_selectedIndex = -1; // 当前选中索引
};
