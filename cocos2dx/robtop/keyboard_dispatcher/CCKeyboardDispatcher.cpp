#include "CCKeyboardDispatcher.h"

namespace cocos2d {

CCKeyboardDispatcher::CCKeyboardDispatcher() {}
CCKeyboardDispatcher::~CCKeyboardDispatcher() {}

// void addDelegate(CCKeyboardDelegate* pDelegate);
// void removeDelegate(CCKeyboardDelegate* pDelegate);

// void forceAddDelegate(CCKeyboardDelegate* pDelegate);
// void forceRemoveDelegate(CCKeyboardDelegate* pDelegate);

// static enumKeyCodes convertKeyCode(enumKeyCodes key);

// bool dispatchKeyboardMSG(enumKeyCodes key, bool isKeyDown, bool isKeyRepeat);

// static GEODE_DLL CCKeyboardDispatcher* get();

// const char* keyToString(enumKeyCodes key);

// void updateModifierKeys(bool shft, bool ctrl, bool alt, bool cmd);


// CCKeyboardHandler

CCKeyboardHandler::~CCKeyboardHandler() {}

CCKeyboardHandler& CCKeyboardHandler::operator=(const CCKeyboardHandler&) {
    std::abort();
    return *this;
}

CCKeyboardDelegate* CCKeyboardHandler::getDelegate() {
    return m_pDelegate;
}

CCKeyboardHandler* CCKeyboardHandler::handlerWithDelegate(CCKeyboardDelegate* pDelegate) {
    auto pRet = new CCKeyboardHandler();
    if (pRet && pRet->initWithDelegate(pDelegate)) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

bool CCKeyboardHandler::initWithDelegate(CCKeyboardDelegate* pDelegate) {
    m_pDelegate = pDelegate;
    return true;
}

void CCKeyboardHandler::setDelegate(CCKeyboardDelegate* pDelegate) {
    m_pDelegate = pDelegate;
}

}