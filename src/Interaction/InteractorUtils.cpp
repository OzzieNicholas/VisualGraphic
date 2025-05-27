#include "../../include/Interaction/InteractorUtils.h"

QVector3D InteractorUtils::mapClickToPlane(float screenX, float screenY,
    const QMatrix4x4& projection,
    const QMatrix4x4& view,
    const QSize& viewportSize) {
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
