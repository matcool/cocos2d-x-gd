#include "CCMouseDispatcher.h"

namespace cocos2d {

CCMouseDispatcher::CCMouseDispatcher() {
    m_pMouseHandlers = CCArray::create();
    m_pMouseHandlers->retain();
    m_bLocked = false;
    m_bToAdd = false;
    m_bToRemove = false;
    m_pHandlersToAdd = ccCArrayNew(8);
    m_pHandlersToRemove = ccCArrayNew(8);
}
CCMouseDispatcher::~CCMouseDispatcher() {
    CC_SAFE_RELEASE(m_pMouseHandlers);
    ccCArrayFree(m_pHandlersToAdd);
    ccCArrayFree(m_pHandlersToRemove);
}

void CCMouseDispatcher::addDelegate(CCMouseDelegate* pDelegate) {
    if (m_bLocked) {
        ccCArrayAppendValue(m_pHandlersToAdd, pDelegate);
        m_bToAdd = true;
    } else {
        forceAddDelegate(pDelegate);
    }
}

void CCMouseDispatcher::removeDelegate(CCMouseDelegate* pDelegate) {
    if (m_bLocked) {
        ccCArrayAppendValue(m_pHandlersToRemove, pDelegate);
        m_bToRemove = true;
    } else {
        forceRemoveDelegate(pDelegate);
    }
}

void CCMouseDispatcher::forceAddDelegate(CCMouseDelegate* pDelegate) {
    m_pMouseHandlers->addObject(CCMouseHandler::handlerWithDelegate(pDelegate));
}

void CCMouseDispatcher::forceRemoveDelegate(CCMouseDelegate* pDelegate) {
    CCMouseHandler* pHandler = nullptr;
    CCObject* pObj = nullptr;
    CCARRAY_FOREACH(m_pMouseHandlers, pObj) {
        pHandler = (CCMouseHandler*)pObj;
        if (pHandler && pHandler->getDelegate() == pDelegate) {
            m_pMouseHandlers->removeObject(pHandler);
            break;
        }
    }
}

bool CCMouseDispatcher::dispatchScrollMSG(float x, float y) {
    m_bLocked = true;
    auto count = m_pMouseHandlers->count();
    CCMouseHandler* pHandler = nullptr;
    CCObject* pObj = nullptr;
    CCARRAY_FOREACH(m_pMouseHandlers, pObj) {
        pHandler = (CCMouseHandler*)pObj;
        pHandler->getDelegate()->scrollWheel(x, y);
    }

    if (m_bToRemove) {
        m_bToRemove = false;
        for (unsigned int i = 0; i < m_pHandlersToRemove->num; ++i) {
            forceRemoveDelegate((CCMouseDelegate*)m_pHandlersToRemove->arr[i]);
        }
        ccCArrayRemoveAllValues(m_pHandlersToRemove);
    }
    if (m_bToAdd) {
        m_bToAdd = false;
        for (unsigned int i = 0; i < m_pHandlersToAdd->num; ++i) {
            forceAddDelegate((CCMouseDelegate*)m_pHandlersToAdd->arr[i]);
        }
        ccCArrayRemoveAllValues(m_pHandlersToAdd);
    }

    m_bLocked = false;

    return true;
}

// CCMouseHandler

CCMouseHandler::~CCMouseHandler() {}

CCMouseHandler& CCMouseHandler::operator=(const CCMouseHandler&) = default;

CCMouseDelegate* CCMouseHandler::getDelegate() {
    return m_pDelegate;
}

CCMouseHandler* CCMouseHandler::handlerWithDelegate(CCMouseDelegate* pDelegate) {
    auto pRet = new CCMouseHandler();
    if (pRet && pRet->initWithDelegate(pDelegate)) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

bool CCMouseHandler::initWithDelegate(CCMouseDelegate* pDelegate) {
    m_pDelegate = pDelegate;
    return true;
}

void CCMouseHandler::setDelegate(CCMouseDelegate* pDelegate) {
    m_pDelegate = pDelegate;
}

}