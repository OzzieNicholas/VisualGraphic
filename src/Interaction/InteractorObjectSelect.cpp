#include "../../include/Interaction/InteractorObjectSelect.h"
#include "../../include/Interaction/InteractorHost.h"
#include "../../include/Interaction/InteractorUtils.h"

InteractorObjectSelect::InteractorObjectSelect() = default;
InteractorObjectSelect::~InteractorObjectSelect() = default;

// ========== �������¼� ========== //

void InteractorObjectSelect::onMousePress(QMouseEvent* event, InteractorHost* host) {
    if (!m_centersRef || m_centersRef->empty()) return;

    float screenX = event->position().x();
    float screenY = event->position().y();

    m_selectedIndex = InteractorUtils::findClosestPointIndex(
        screenX,
        screenY,
        *m_centersRef,
        host->getProjectionMatrix(),
        host->getViewMatrix(),
        host->getViewportSize(),
        m_pickRadius
    );

    host->requestViewportUpdate();
}

void InteractorObjectSelect::onMouseMove(QMouseEvent*, InteractorHost*) {
    // ������Ϊ
}

void InteractorObjectSelect::onWheel(QWheelEvent*, InteractorHost*) {
    // ������Ϊ
}

void InteractorObjectSelect::onKeyPress(QKeyEvent* event, InteractorHost* host) {
    if (event->key() == Qt::Key_Escape) {
        clearSelection();
        host->requestViewportUpdate();
    }
}

// ========== ѡ����� ========== //

// ���ÿ�ѡ�����Ŀռ�λ��
void InteractorObjectSelect::setSelectableCenters(const std::vector<QVector3D>* centers) {
    m_centersRef = centers;
    m_selectedIndex = -1;
}

// ����ʰȡ�ݲ�
void InteractorObjectSelect::setPickRadius(float radius) {
    m_pickRadius = radius;
}

// ��ȡ��ǰѡ�ж���������-1 ��ʾ��ѡ�У�
int InteractorObjectSelect::getSelectedIndex() const {
    return m_selectedIndex;
}

// �����ǰѡ��״̬
void InteractorObjectSelect::clearSelection() {
    m_selectedIndex = -1;
}
