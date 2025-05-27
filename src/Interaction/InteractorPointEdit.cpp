#include "../../include/Interaction/InteractorPointEdit.h"
#include "../../include/Interaction/InteractorHost.h"
#include "../../include/Interaction/InteractorUtils.h"
#include "../../include/Geometry/MeshLineBuilder.h"

#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <limits>

InteractorPointEdit::InteractorPointEdit() = default;
InteractorPointEdit::~InteractorPointEdit() = default;

// ========== 鼠标键盘事件 ========== //

void InteractorPointEdit::onMousePress(QMouseEvent* event, InteractorHost* host) {
    if (!m_pointsRef || m_pointsRef->empty()) return;

    const auto projection = host->getProjectionMatrix();
    const auto view = host->getViewMatrix();
    const auto viewport = host->getViewportSize();

    const float x = event->position().x();
    const float y = event->position().y();

    // 拾取最近点索引
    m_selectedIndex = InteractorUtils::findClosestPointIndex(
        x, y, *m_pointsRef, projection, view, viewport, m_pickRadius
    );

    m_lastMousePos = event->pos();
}

void InteractorPointEdit::onMouseMove(QMouseEvent* event, InteractorHost* host) {
    if (!m_pointsRef || m_selectedIndex < 0 || m_selectedIndex >= int(m_pointsRef->size())) return;

    if (event->buttons() & Qt::LeftButton) {
        const auto projection = host->getProjectionMatrix();
        const auto view = host->getViewMatrix();
        const auto viewport = host->getViewportSize();

        const float x = event->position().x();
        const float y = event->position().y();

        // 将屏幕位置映射到 Z=0 平面
        QVector3D worldPoint = InteractorUtils::mapClickToPlane(x, y, projection, view, viewport);

        // 更新点位置
        (*m_pointsRef)[m_selectedIndex] = worldPoint;

        // 更新折线预览
        auto preview = MeshLineBuilder::buildPolylineMesh(*m_pointsRef, QVector3D(0.8f, 0.2f, 0.2f));
        host->setPolylineMesh(preview);

        host->requestViewportUpdate();
    }

    m_lastMousePos = event->pos();
}

void InteractorPointEdit::onWheel(QWheelEvent*, InteractorHost*) {
    // 点编辑器不处理缩放
}

void InteractorPointEdit::onKeyPress(QKeyEvent* event, InteractorHost* host) {
    if (event->key() == Qt::Key_Escape) {
        m_selectedIndex = -1;
        host->requestViewportUpdate();
    }
}

// ========== 点编辑操作 ========== //

// 设置待编辑的点引用
void InteractorPointEdit::setTargetPoints(std::vector<QVector3D>* points) {
    m_pointsRef = points;
    m_selectedIndex = -1;
}

// 设置拾取半径（屏幕像素）
void InteractorPointEdit::setPickRadius(float radius) {
    m_pickRadius = radius;
}
