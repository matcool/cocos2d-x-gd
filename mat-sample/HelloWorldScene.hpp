#pragma once

#include <cocos2d.h>

using namespace cocos2d;

class HelloWorld : public CCLayer {
public:
	bool init() override;

	static CCScene* scene();

	CREATE_FUNC(HelloWorld);
};
