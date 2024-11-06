#include "AppDelegate.hpp"
#include "HelloWorldScene.hpp"

#include <filesystem>

// void AppDelegate::setupGLView() {
// 	auto* director = CCDirector::sharedDirector();

// 	auto* glView = CCEGLView::createWithRect("Hello!", CCRect(0, 0, 1280, 720), 1.0f);
// 	director->setOpenGLView(glView);

// 	director->setupScreenScale({480, 320}, {1280, 720}, TextureQuality::kTextureQualityHigh);
// }

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	CCSize frameSize = pEGLView->getFrameSize();

    // pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);

    // set searching path
    auto cwd = std::filesystem::current_path();
    CCFileUtils::sharedFileUtils()->addSearchPath((cwd / "Resources").string().c_str());
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {}

void AppDelegate::applicationWillEnterForeground() {}
