#include "CCContentManager.h"

using namespace cocos2d;

CCContentManager* CCContentManager::sharedManager() {
    static CCContentManager* sharedManager = nullptr;
    if (!sharedManager) {
        sharedManager = new CCContentManager();
        sharedManager->init();
    }
    return sharedManager;
}
CCContentManager::CCContentManager() {}
CCContentManager::~CCContentManager() {
    m_pDicts->release();
}
bool CCContentManager::init() {
    m_pDicts = CCDictionary::create();
    m_pDicts->retain();
    return true;
}

cocos2d::CCDictionary* CCContentManager::addDict(const char* dict, bool unk) {
    ROB_UNIMPLEMENTED();
}
cocos2d::CCDictionary* CCContentManager::addDictDS(const char* dict) {
    ROB_UNIMPLEMENTED();
}

void CCContentManager::clearCache() {
    ROB_UNIMPLEMENTED();
}