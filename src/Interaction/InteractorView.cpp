#include "../../include/Interaction/InteractorView.h"
#include "../../include/Interaction/InteractorHost.h"

InteractorView::InteractorView() = default;
InteractorView::~InteractorView() = default;

void InteractorView::onMousePress(QMouseEvent* event, InteractorHost* host) {
    m_lastMousePos = event->pos();
}

void InteractorView::onMouseMove(QMouseEvent* event, InteractorHost* host) {
    QPoint delta = event->pos() - m_lastMousePos;

    if (event->buttons() & Qt::LeftButton) {
        float dx = delta.x();
        float dy = delta.y();

        // 旋转量比例可调
        float angleScale = 0.5f;
        host->rotateView(dx * angleScale, dy * angleScale);
    }
    else if (event->buttons() & Qt::RightButton) {
        float px = delta.x() * 0.01f;
        float py = -delta.y() * 0.01f;
        host->panView(px, py);
    }

    m_lastMousePos = event->pos();
    host->requestViewportUpdate();
}

void InteractorView::onWheel(QWheelEvent* event, InteractorHost* host) {
    float zoomDelta = -event->angleDelta().y() / 120.0f;
    host->zoomView(zoomDelta);
    host->requestViewportUpdate();
}

void InteractorView::onKeyPress(QKeyEvent* event, InteractorHost* host) {
    // 视角控制默认不响应键盘事件
    Q_UNUSED(event);
    Q_UNUSED(host);
}
