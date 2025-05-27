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

// ========== �������¼� ========== //

void InteractorPointEdit::onMousePress(QMouseEvent* event, InteractorHost* host) {
    if (!m_pointsRef || m_pointsRef->empty()) return;

    const auto projection = host->getProjectionMatrix();
    const auto view = host->getViewMatrix();
    const auto viewport = host->getViewportSize();

    const float x = event->position().x();
    const float y = event->position().y();

    // ʰȡ���������
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

        // ����Ļλ��ӳ�䵽 Z=0 ƽ��
        QVector3D worldPoint = InteractorUtils::mapClickToPlane(x, y, projection, view, viewport);

        // ���µ�λ��
        (*m_pointsRef)[m_selectedIndex] = worldPoint;

        // ��������Ԥ��
        auto preview = MeshLineBuilder::buildPolylineMesh(*m_pointsRef, QVector3D(0.8f, 0.2f, 0.2f));
        host->setPolylineMesh(preview);

        host->requestViewportUpdate();
    }

    m_lastMousePos = event->pos();
}

void InteractorPointEdit::onWheel(QWheelEvent*, InteractorHost*) {
    // ��༭������������
}

void InteractorPointEdit::onKeyPress(QKeyEvent* event, InteractorHost* host) {
    if (event->key() == Qt::Key_Escape) {
        m_selectedIndex = -1;
        host->requestViewportUpdate();
    }
}

// ========== ��༭���� ========== //

// ���ô��༭�ĵ�����
void InteractorPointEdit::setTargetPoints(std::vector<QVector3D>* points) {
    m_pointsRef = points;
    m_selectedIndex = -1;
}

// ����ʰȡ�뾶����Ļ���أ�
void InteractorPointEdit::setPickRadius(float radius) {
    m_pickRadius = radius;
}
