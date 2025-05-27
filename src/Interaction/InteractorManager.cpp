#include "../../include/Interaction/InteractorManager.h"
#include "../../include/Interaction/InteractorBase.h"
#include "../../include/Interaction/InteractorHost.h"

InteractorManager::InteractorManager() = default;

InteractorManager::~InteractorManager() = default;

void InteractorManager::setActiveInteractor(std::shared_ptr<InteractorBase> interactor) {
    m_activeInteractor = interactor;
}

std::shared_ptr<InteractorBase> InteractorManager::getActiveInteractor() const {
    return m_activeInteractor;
}

void InteractorManager::clearActiveInteractor() {
    m_activeInteractor.reset();
}

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

// ÅÐ¶ÏÊÇ·ñ´æÔÚ½»»¥Æ÷
bool InteractorManager::hasActiveInteractor() const {
    return static_cast<bool>(m_activeInteractor);
}
