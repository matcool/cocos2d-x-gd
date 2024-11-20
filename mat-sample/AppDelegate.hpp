#pragma once

#include <cocos2d.h>

using namespace cocos2d;

class AppDelegate : public CCApplication {
public:
	AppDelegate() {}
	virtual ~AppDelegate() {}

	bool applicationDidFinishLaunching() override;

	void applicationDidEnterBackground() override;

	void applicationWillEnterForeground() override;

	void setupGLView() override;
};
