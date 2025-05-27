#include "../../include/Interaction/InteractorObjectSelect.h"
#include "../../include/Interaction/InteractorHost.h"
#include "../../include/Interaction/InteractorUtils.h"

InteractorObjectSelect::InteractorObjectSelect() = default;
InteractorObjectSelect::~InteractorObjectSelect() = default;

// ========== 鼠标键盘事件 ========== //

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
    // 暂无行为
}

void InteractorObjectSelect::onWheel(QWheelEvent*, InteractorHost*) {
    // 暂无行为
}

void InteractorObjectSelect::onKeyPress(QKeyEvent* event, InteractorHost* host) {
    if (event->key() == Qt::Key_Escape) {
        clearSelection();
        host->requestViewportUpdate();
    }
}

// ========== 选择对象 ========== //

// 设置可选择对象的空间位置
void InteractorObjectSelect::setSelectableCenters(const std::vector<QVector3D>* centers) {
    m_centersRef = centers;
    m_selectedIndex = -1;
}

// 设置拾取容差
void InteractorObjectSelect::setPickRadius(float radius) {
    m_pickRadius = radius;
}

// 获取当前选中对象索引（-1 表示无选中）
int InteractorObjectSelect::getSelectedIndex() const {
    return m_selectedIndex;
}

// 清除当前选中状态
void InteractorObjectSelect::clearSelection() {
    m_selectedIndex = -1;
}
