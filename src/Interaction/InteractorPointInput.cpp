#include "../../include/Interaction/InteractorPointInput.h"
#include "../../include/Interaction/InteractorHost.h"
#include "../../include/Interaction/InteractorUtils.h"

#include "../../include/Geometry/MeshLineBuilder.h"

InteractorPointInput::InteractorPointInput() = default;

InteractorPointInput::~InteractorPointInput() = default;

// ========== �������¼� ========== //

void InteractorPointInput::onMousePress(QMouseEvent* event, InteractorHost* host) {
    if (event->button() == Qt::LeftButton) {
        const QMatrix4x4 proj = host->getProjectionMatrix();
        const QMatrix4x4 view = host->getViewMatrix();
        const QSize viewport = host->getViewportSize();

        QVector3D worldPoint = InteractorUtils::mapClickToPlane(
            event->position().x(),
            event->position().y(),
            proj, view, viewport
        );

        if (!std::isnan(worldPoint.x())) {
            m_inputPoints.push_back(worldPoint);

            auto previewMesh = MeshLineBuilder::buildPolylineMesh(m_inputPoints, QVector3D(1.0f, 0.0f, 0.0f));
            host->setPolylineMesh(previewMesh);

            host->requestViewportUpdate();
        }
    }
}

void InteractorPointInput::onMouseMove(QMouseEvent* event, InteractorHost* host) {
    Q_UNUSED(event);
    Q_UNUSED(host);
}

void InteractorPointInput::onWheel(QWheelEvent* event, InteractorHost* host) {
    Q_UNUSED(event);
    Q_UNUSED(host);
}

void InteractorPointInput::onKeyPress(QKeyEvent* event, InteractorHost* host) {
    if (event->key() == Qt::Key_Escape) {
        clearInputPoints();
        host->clearPolyline();
        host->requestViewportUpdate();
    }
}

// ========== �����Ĵ��� ========== //

// ��ȡ�����
const std::vector<QVector3D>& InteractorPointInput::getInputPoints() const {
    return m_inputPoints;
}

// ��������
void InteractorPointInput::clearInputPoints() {
    m_inputPoints.clear();
}
