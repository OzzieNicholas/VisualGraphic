#include "../../include/Interaction/InteractorUtils.h"
#include <cmath>
#include <limits>

// 点转换为平面世界坐标
QVector3D InteractorUtils::mapClickToPlane(
    float screenX,
    float screenY,
    const QMatrix4x4& projection,
    const QMatrix4x4& view,
    const QSize& viewportSize
) {
    float ndcX = (2.0f * screenX) / viewportSize.width() - 1.0f;
    float ndcY = 1.0f - (2.0f * screenY) / viewportSize.height();

    QMatrix4x4 invPV = (projection * view).inverted();

    QVector4D nearNDC(ndcX, ndcY, -1.0f, 1.0f);
    QVector4D farNDC(ndcX, ndcY, 1.0f, 1.0f);

    QVector4D nearWorld = invPV * nearNDC;
    QVector4D farWorld = invPV * farNDC;

    nearWorld /= nearWorld.w();
    farWorld /= farWorld.w();

    QVector3D rayOrigin = nearWorld.toVector3D();
    QVector3D rayDir = (farWorld - nearWorld).toVector3D().normalized();

    if (qAbs(rayDir.z()) < 1e-6f) {
		return QVector3D(
            std::numeric_limits<float>::infinity(),
			std::numeric_limits<float>::infinity(),
			std::numeric_limits<float>::infinity()
        );
    }

    float t = -rayOrigin.z() / rayDir.z();
    return rayOrigin + t * rayDir;
}

// 从点集中找出与点击位置最近的点索引（若超出容差则返回 -1）
int InteractorUtils::findClosestPointIndex(
    float screenX,
    float screenY,
    const std::vector<QVector3D>& worldPoints,
    const QMatrix4x4& projection,
    const QMatrix4x4& view,
    const QSize& viewportSize,
    float maxPixelRadius
) {
    float minDistSquared = std::numeric_limits<float>::max();
    int bestIndex = -1;

    QMatrix4x4 pv = projection * view;

    for (int i = 0; i < int(worldPoints.size()); ++i) {
        QVector4D clip = pv * QVector4D(worldPoints[i], 1.0f);
        if (clip.w() == 0.0f) continue;

        QVector3D ndc = clip.toVector3DAffine();
        float winX = (ndc.x() * 0.5f + 0.5f) * viewportSize.width();
        float winY = (1.0f - ndc.y()) * 0.5f * viewportSize.height();

        float dx = winX - screenX;
        float dy = winY - screenY;
        float distSq = dx * dx + dy * dy;

        if (distSq < minDistSquared && distSq < maxPixelRadius * maxPixelRadius) {
            minDistSquared = distSq;
            bestIndex = i;
        }
    }

    return bestIndex;
}
