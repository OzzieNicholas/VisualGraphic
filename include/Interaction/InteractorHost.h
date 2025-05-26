/*
 * InteractorHost.h：交互控件能力接口
 *
 * 功能概述：
 *  - 定义所有交互行为所需的控件数据接口
 *  - 提供投影/视图矩阵、尺寸、坐标投影等
 *  - 用于交互器（InteractorBase）访问控件上下文
 *
 * 使用场景：
 *  - 由 Widget 或其他可交互控件实现
 *  - 供所有 InteractorXxx 类访问控件状态
 */

#pragma once

#include <QMatrix4x4>
#include <QSize>

class InteractorHost {
public:
    virtual ~InteractorHost() = default;

    // ========== 控件基础接口 ========== //

    // 获取视图矩阵
    virtual QMatrix4x4 getViewMatrix() const = 0;

    // 获取投影矩阵
    virtual QMatrix4x4 getProjectionMatrix() const = 0;

    // 获取控件尺寸（像素）
    virtual QSize getViewportSize() const = 0;

    // 请求控件更新（重绘）
    virtual void requestViewportUpdate() = 0;

    // 获取世界中 Z=0 平面的点映射辅助
    virtual float getCameraZoom() const = 0;
};
