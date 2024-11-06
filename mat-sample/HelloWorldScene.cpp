#include "HelloWorldScene.hpp"

CCScene* HelloWorld::scene() {
	auto* scene = CCScene::create();
	auto* layer = HelloWorld::create();
	scene->addChild(layer);

	return scene;
}

bool HelloWorld::init() {
	if (!CCLayer::init()) {
		return false;
	}
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	auto* label = CCLabelBMFont::create("Hello World", "bigFont-hd.fnt");
	label->setPosition(winSize / 2);
	this->addChild(label);

	auto* sprite = CCSprite::create("game_bg_07_001-hd.png");
	sprite->setZOrder(-100);
	sprite->setColor({122, 179, 239});
	sprite->setPosition(winSize / 2);
	sprite->setScale(1.9f);
	this->addChild(sprite);

	return true;
}
