/*
 * InteractorHost.h：交互控件能力接口
 *
 * 功能概述：
 *  - 定义所有交互行为所需的控件数据接口
 *  - 提供投影/视图矩阵、尺寸、坐标投影等
 *  - 提供视角操作接口（旋转、平移、缩放）
 *
 * 使用场景：
 *  - 由 Widget 或其他可交互控件实现
 *  - 供所有 InteractorXxx 类访问控件状态
 *  - 与 InteractorView 协同用于场景导航交互
 */

#pragma once

#include <QMatrix4x4>
#include <QSize>

class InteractorHost {
public:
    virtual ~InteractorHost() = default;

    // ========== 控件基础 ========== //

    // 获取视图矩阵
    virtual QMatrix4x4 getViewMatrix() const = 0;

    // 获取投影矩阵
    virtual QMatrix4x4 getProjectionMatrix() const = 0;

    // 获取控件尺寸（像素）
    virtual QSize getViewportSize() const = 0;

    // 请求控件更新（重绘）
    virtual void requestViewportUpdate() = 0;

    // 获取相机距离（可用于深度调整）
    virtual float getCameraZoom() const = 0;

    // ========== 视角操作 ========== //

    // 旋转视角（绕 X、Y）
    virtual void rotateView(float deltaX, float deltaY) = 0;

    // 平移视角（平移平面为屏幕平面）
    virtual void panView(float offsetX, float offsetY) = 0;

    // 缩放视角（通过相机距离控制）
    virtual void zoomView(float zoomDelta) = 0;
};
