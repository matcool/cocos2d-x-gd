#include "CCMouseDispatcher.h"

namespace cocos2d {

CCMouseDispatcher::CCMouseDispatcher() {}
CCMouseDispatcher::~CCMouseDispatcher() {}

void CCMouseDispatcher::addDelegate(CCMouseDelegate* pDelegate) {
    ROB_UNIMPLEMENTED();
}

void CCMouseDispatcher::removeDelegate(CCMouseDelegate* pDelegate) {
    ROB_UNIMPLEMENTED();
}

void CCMouseDispatcher::forceAddDelegate(CCMouseDelegate* pDelegate) {
    ROB_UNIMPLEMENTED();
}

void CCMouseDispatcher::forceRemoveDelegate(CCMouseDelegate* pDelegate) {
    ROB_UNIMPLEMENTED();
}

bool CCMouseDispatcher::dispatchScrollMSG(float x, float y) {
    ROB_UNIMPLEMENTED();
}

// CCMouseHandler

CCMouseHandler::~CCMouseHandler() {}

CCMouseHandler& CCMouseHandler::operator=(const CCMouseHandler&) {
    ROB_UNIMPLEMENTED();
    return *this;
}

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