#include "CCKeyboardDispatcher.h"

namespace cocos2d {

CCKeyboardDispatcher::CCKeyboardDispatcher() {
    m_pHandlers = CCArray::create();
    m_pHandlers->retain();
    m_bLocked = false;
    m_bToAdd = false;
    m_bToRemove = false;
    m_pHandlersToAdd = ccCArrayNew(8);
    m_pHandlersRemove = ccCArrayNew(8);
    m_bShiftPressed = false;
    m_bControlPressed = false;
    m_bAltPressed = false;
    m_bCommandPressed = false;
    m_bBlockRepeat = false;
}
CCKeyboardDispatcher::~CCKeyboardDispatcher() {
    CC_SAFE_RELEASE(m_pHandlers);
    ccCArrayFree(m_pHandlersToAdd);
    ccCArrayFree(m_pHandlersRemove);
}

void CCKeyboardDispatcher::addDelegate(CCKeyboardDelegate* pDelegate) {
    if (m_bLocked) {
        ccCArrayAppendValue(m_pHandlersToAdd, pDelegate);
        m_bToAdd = true;
    } else {
        forceAddDelegate(pDelegate);
    }
}
void CCKeyboardDispatcher::removeDelegate(CCKeyboardDelegate* pDelegate) {
    if (m_bLocked) {
        ccCArrayAppendValue(m_pHandlersRemove, pDelegate);
        m_bToRemove = true;
    } else {
        forceRemoveDelegate(pDelegate);
    }
}

void CCKeyboardDispatcher::forceAddDelegate(CCKeyboardDelegate* pDelegate) {
    m_pHandlers->addObject(CCKeyboardHandler::handlerWithDelegate(pDelegate));
}
void CCKeyboardDispatcher::forceRemoveDelegate(CCKeyboardDelegate* pDelegate) {
    CCKeyboardHandler* pHandler = nullptr;
    CCObject* pObj = nullptr;
    CCARRAY_FOREACH(m_pHandlers, pObj) {
        pHandler = (CCKeyboardHandler*)pObj;
        if (pHandler && pHandler->getDelegate() == pDelegate) {
            m_pHandlers->removeObject(pHandler);
            break;
        }
    }
}

enumKeyCodes CCKeyboardDispatcher::convertKeyCode(enumKeyCodes key) {
    switch (key) {
        case KEY_ArrowUp:
            return KEY_Up;
        case KEY_ArrowDown:
            return KEY_Down;
        case KEY_ArrowLeft:
            return KEY_Left;
        case KEY_ArrowRight:
            return KEY_Right;
        default:
            return key;
    }
}

bool CCKeyboardDispatcher::dispatchKeyboardMSG(enumKeyCodes key, bool isKeyDown, bool isKeyRepeat) {
    if (m_bBlockRepeat && isKeyRepeat) {
        return false;
    }
    key = convertKeyCode(key);
    switch (key) {
        case KEY_Shift:
        case KEY_Control:
        case KEY_Alt:
        case KEY_Escape:
            return false;
        default:
            break;
    }
    m_bLocked = true;
    auto count = m_pHandlers->count();
    CCKeyboardHandler* pHandler = nullptr;
    CCObject* pObj = nullptr;
    CCARRAY_FOREACH(m_pHandlers, pObj) {
        pHandler = (CCKeyboardHandler*)pObj;
        if (isKeyDown) {
            pHandler->getDelegate()->keyDown(key);
        } else {
            pHandler->getDelegate()->keyUp(key);
        }
    }

    if (m_bToRemove) {
        m_bToRemove = false;
        for (unsigned int i = 0; i < m_pHandlersRemove->num; ++i) {
            forceRemoveDelegate((CCKeyboardDelegate*)m_pHandlersRemove->arr[i]);
        }
        ccCArrayRemoveAllValues(m_pHandlersRemove);
    }
    if (m_bToAdd) {
        m_bToAdd = false;
        for (unsigned int i = 0; i < m_pHandlersToAdd->num; ++i) {
            forceAddDelegate((CCKeyboardDelegate*)m_pHandlersToAdd->arr[i]);
        }
        ccCArrayRemoveAllValues(m_pHandlersToAdd);
    }

    m_bLocked = false;

    return true;
}

const char* CCKeyboardDispatcher::keyToString(enumKeyCodes key) {
    // TODO: possibly implement this
    return "PLACEHOLDER_KEY";
}

void CCKeyboardDispatcher::updateModifierKeys(bool shft, bool ctrl, bool alt, bool cmd) {
    m_bShiftPressed = shft;
    m_bControlPressed = ctrl || cmd;
    m_bAltPressed = alt;
    m_bCommandPressed = cmd;
}
// CCKeyboardHandler

CCKeyboardHandler::~CCKeyboardHandler() {}

CCKeyboardHandler& CCKeyboardHandler::operator=(const CCKeyboardHandler&) = default;

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