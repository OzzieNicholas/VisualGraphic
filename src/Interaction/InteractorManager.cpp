#include "../../include/Interaction/InteractorManager.h"
#include "../../include/Interaction/InteractorBase.h"
#include "../../include/Interaction/InteractorHost.h"

InteractorManager::InteractorManager() = default;

InteractorManager::~InteractorManager() = default;

// ========== 鼠标键盘事件 ========== //

void InteractorManager::onMousePress(QMouseEvent* event, InteractorHost* host) {
    if (m_activeInteractor) {
        m_activeInteractor->onMousePress(event, host);
    }
}

void InteractorManager::onMouseMove(QMouseEvent* event, InteractorHost* host) {
    if (m_activeInteractor) {
        m_activeInteractor->onMouseMove(event, host);
    }
}

void InteractorManager::onWheel(QWheelEvent* event, InteractorHost* host) {
    if (m_activeInteractor) {
        m_activeInteractor->onWheel(event, host);
    }
}

void InteractorManager::onKeyPress(QKeyEvent* event, InteractorHost* host) {
    if (m_activeInteractor) {
        m_activeInteractor->onKeyPress(event, host);
    }
}

// ========== 交互器管理 ========== //

// 设置交互器
void InteractorManager::setActiveInteractor(std::shared_ptr<InteractorBase> interactor) {
    m_activeInteractor = interactor;
}

// 获取交互器
std::shared_ptr<InteractorBase> InteractorManager::getActiveInteractor() const {
    return m_activeInteractor;
}

// 判断是否存在交互器
bool InteractorManager::hasActiveInteractor() const {
    return static_cast<bool>(m_activeInteractor);
}

// 清除交互器
void InteractorManager::clearActiveInteractor() {
    m_activeInteractor.reset();
}

