#include "CCContentManager.h"
#include "robtop/xml/DS_Dictionary.h"

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

CCDictionary* CCContentManager::addDict(const char* filePath, bool unk) {
    auto* obj = static_cast<CCDictionary*>(m_pDicts->objectForKey(filePath));
    if (obj == nullptr) {
        auto* dsDict = new DS_Dictionary();
        dsDict->loadRootSubDictFromFile(filePath);
        obj = dsDict->getDictForKey(nullptr, false);
        m_pDicts->setObject(obj, filePath);
    }
    return obj;
}
cocos2d::CCDictionary* CCContentManager::addDictDS(const char* dict) {
    ROB_UNIMPLEMENTED();
}

void CCContentManager::clearCache() {
    ROB_UNIMPLEMENTED();
}