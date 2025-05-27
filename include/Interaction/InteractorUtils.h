/*
 * InteractorUtils.h：交互辅助函数工具集
 *
 * 功能概述：
 *  - 提供常用的点击点映射、坐标转换等操作
 *  - 交互器模块共享工具函数，不依赖控件类型
 *
 * 使用场景：
 *  - InteractorXxx 中进行点击点 → 世界坐标转换
 *  - 用于绘制辅助几何体、拾取点投影、控制输入校准等
 *  - 与 InteractorHost 配合使用，提供通用交互变换支持
 */

#pragma once

#include <QVector3D>
#include <QMatrix4x4>
#include <QSize>

namespace InteractorUtils {
    // 点转换为平面世界坐标
    QVector3D mapClickToPlane(
        float screenX,
        float screenY,
        const QMatrix4x4& projection,
        const QMatrix4x4& view,
        const QSize& viewportSize
    );

    // 从点集中找出与点击位置最近的点索引（若超出容差则返回 -1）
    int findClosestPointIndex(
        float screenX,
        float screenY,
        const std::vector<QVector3D>& worldPoints,
        const QMatrix4x4& projection,
        const QMatrix4x4& view,
        const QSize& viewportSize,
        float maxPixelRadius = 8.0f
    );
}
