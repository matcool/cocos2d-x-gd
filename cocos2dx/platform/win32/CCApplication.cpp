#include "CCApplication.h"
#include "CCEGLView.h"
#include "CCDirector.h"
#include <algorithm>
#include "platform/CCFileUtils.h"
#include <robtop/mouse_dispatcher/CCMouseDispatcher.h>

NS_CC_BEGIN

// sharedApplication pointer
CCApplication * CCApplication::sm_pSharedApplication = 0;

CCApplication::CCApplication()
: m_hInstance(NULL)
, m_hAccelTable(NULL)
{
    m_hInstance    = GetModuleHandle(NULL);
    m_nAnimationInterval.QuadPart = 0;
    CC_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;
}

CCApplication::~CCApplication()
{
    CC_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = NULL;
}

int CCApplication::run()
{
    this->setupGLView();

    this->setupVerticalSync();
    this->updateVerticalSync();

    this->applicationDidFinishLaunching();

    auto* egl = CCEGLView::sharedOpenGLView();
    auto* dir = CCDirector::sharedDirector();

    glfwSwapInterval(1);

    while (!egl->windowShouldClose()) {
        egl->pollEvents();
        dir->mainLoop();
    }

    dir->end();

    return 0;
}

void CCApplication::setAnimationInterval(double interval)
{
    LARGE_INTEGER nFreq;
    QueryPerformanceFrequency(&nFreq);
    m_nAnimationInterval.QuadPart = (LONGLONG)(interval * nFreq.QuadPart);
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
CCApplication* CCApplication::sharedApplication()
{
    CC_ASSERT(sm_pSharedApplication);
    return sm_pSharedApplication;
}

ccLanguageType CCApplication::getCurrentLanguage()
{
    ccLanguageType ret = kLanguageEnglish;

    LCID localeID = GetUserDefaultLCID();
    unsigned short primaryLanguageID = localeID & 0xFF;
    
    switch (primaryLanguageID)
    {
        case LANG_CHINESE:
            ret = kLanguageChinese;
            break;
        case LANG_ENGLISH:
            ret = kLanguageEnglish;
            break;
        case LANG_FRENCH:
            ret = kLanguageFrench;
            break;
        case LANG_ITALIAN:
            ret = kLanguageItalian;
            break;
        case LANG_GERMAN:
            ret = kLanguageGerman;
            break;
        case LANG_SPANISH:
            ret = kLanguageSpanish;
            break;
        case LANG_DUTCH:
            ret = kLanguageDutch;
            break;
        case LANG_RUSSIAN:
            ret = kLanguageRussian;
            break;
        case LANG_KOREAN:
            ret = kLanguageKorean;
            break;
        case LANG_JAPANESE:
            ret = kLanguageJapanese;
            break;
        case LANG_HUNGARIAN:
            ret = kLanguageHungarian;
            break;
        case LANG_PORTUGUESE:
            ret = kLanguagePortuguese;
            break;
        case LANG_ARABIC:
            ret = kLanguageArabic;
            break;
    }

    return ret;
}

TargetPlatform CCApplication::getTargetPlatform()
{
    return kTargetWindows;
}

void CCApplication::setResourceRootPath(const std::string& rootResDir)
{
    m_resourceRootPath = rootResDir;
    std::replace(m_resourceRootPath.begin(), m_resourceRootPath.end(), '\\', '/');
    if (m_resourceRootPath[m_resourceRootPath.length() - 1] != '/')
    {
        m_resourceRootPath += '/';
    }
    CCFileUtils* pFileUtils = CCFileUtils::sharedFileUtils();
    std::vector<std::string> searchPaths = pFileUtils->getSearchPaths();
    searchPaths.insert(searchPaths.begin(), m_resourceRootPath);
    pFileUtils->setSearchPaths(searchPaths);
}

const std::string& CCApplication::getResourceRootPath(void)
{
    return m_resourceRootPath;
}

void CCApplication::setStartupScriptFilename(const std::string& startupScriptFile)
{
    m_startupScriptFilename = startupScriptFile;
    std::replace(m_startupScriptFilename.begin(), m_startupScriptFilename.end(), '\\', '/');
}

void cocos2d::CCApplication::gameDidSave(void) {
    if (m_bShutdownCalled) {
        CCDirector::sharedDirector()->end();
    }
}
void cocos2d::CCApplication::openURL(char const * url) {
    auto* glView = CCEGLView::sharedOpenGLView();
    if (glView->m_bIsFullscreen) {
        if (!glView->m_bIsBorderless) {
            glView->iconify();
        }
    }
    ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}
void cocos2d::CCApplication::setupGLView(void) {
    auto* glview = CCEGLView::create("Try again");
    CCDirector::sharedDirector()->setOpenGLView(glview);
}
void cocos2d::CCApplication::platformShutdown(void) {
    
}

void CCApplication::setupVerticalSync() {
    // glfwSwapInterval(1);
}

void CCApplication::updateVerticalSync() {

}

void CCApplication::toggleVerticalSync(bool) {
    this->updateVerticalSync();
}

void CCApplication::toggleMouseControl(bool control) {
    m_bMouseControl = control;
}

void CCApplication::updateMouseControl() {
    auto* egl = CCEGLView::sharedOpenGLView();
    auto* dir = CCDirector::sharedDirector();
    if (!egl->getShouldHideCursor() && !egl->getCursorLocked()) {
        if (m_obRightThumb != ccp(0, 0)) {
            dir->getMouseDispatcher()->dispatchScrollMSG(m_obRightThumb.x, -m_obRightThumb.y);
        }
        if (m_obLeftThumb != ccp(0, 0)) {
            this->moveMouse(m_obLeftThumb.x, m_obLeftThumb.y);
        }
    }
}

void CCApplication::moveMouse(int relX, int relY) {
    auto* egl = CCEGLView::sharedOpenGLView();
    glfwSetCursorPos(egl->getWindow(), egl->getMousePosition().x + relX, egl->getMousePosition().y + relY);
}

NS_CC_END
