#include <cocos2d.h>
#include "AppDelegate.hpp"

int main() {
	AppDelegate app;

    auto* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("HelloCpp");
    eglView->setFrameSize(1280, 720);

	CCApplication::sharedApplication()->run();
}
