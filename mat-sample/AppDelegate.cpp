#include "AppDelegate.hpp"
#include "HelloWorldScene.hpp"

#include <filesystem>

void AppDelegate::setupGLView() {
	auto* director = CCDirector::sharedDirector();

	auto* glView = CCEGLView::createWithRect("Hello!", CCRect(0, 0, 1280, 720), 1.0f);
	director->setOpenGLView(glView);

	director->setupScreenScale({480, 320}, {1280, 720}, TextureQuality::kTextureQualityHigh);
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto* director = CCDirector::sharedDirector();
    director->setAlphaBlending(true);

#ifdef _WIN32
    auto cwd = std::filesystem::current_path();
    CCFileUtils::sharedFileUtils()->addSearchPath((cwd / "Resources").string().c_str());
#else
    CCFileUtils::sharedFileUtils()->addSearchPath("/Resources");
#endif

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);

    auto* scene = HelloWorld::scene();
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {}

void AppDelegate::applicationWillEnterForeground() {}
