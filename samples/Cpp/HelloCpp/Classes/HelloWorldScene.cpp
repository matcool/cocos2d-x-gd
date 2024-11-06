#include "HelloWorldScene.h"
#include "AppMacros.h"
USING_NS_CC;


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

    if (!CCLayer::init())
        return false;
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCFileUtils::sharedFileUtils()->addSearchPath("Resources");


    std::cout << "hello :D" << std::endl;

    auto path = CCFileUtils::sharedFileUtils()->fullPathForFilename("test.png");
    std::cout << "full path is " << path << std::endl;

    CCSprite* pSprite = CCSprite::create("GJ_button_01.png");
    std::cout << pSprite << std::endl;
    // std::cout << CCSprite::create("test.jpeg") << std::endl;
    // std::cout << CCSprite::create("test.png") << std::endl;
    // std::cout << CCSprite::create("test.tiff") << std::endl;

    if (pSprite) {
        pSprite->setPosition({100, 100});
        pSprite->setScale(10.0);

        this->addChild(pSprite);
    }

    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
