#pragma once

#include <cocos2d.h>

using namespace cocos2d;

class HelloWorld : public CCLayer {
	CCLabelBMFont* m_label;
public:
	bool init() override;

	static CCScene* scene();

	CREATE_FUNC(HelloWorld);

	bool ccTouchBegan(CCTouch* touch, CCEvent*) override;
	void ccTouchMoved(CCTouch* touch, CCEvent*) override;
};
