#include "SummonMenuScene.h"
#include "MainMenuScene.h"
USING_NS_CC;

Scene* SummonMenuScene::createScene()
{
    return SummonMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SummonMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    setScene(this);

    cocos2d::Label* Banner = newLabel("Current Banner");
    Banner->setPosition(250, 580);

    cocos2d::Label* Single = newLabel("Single Summons");
    Single->setPosition(120, 440);
    Single->setAnchorPoint(Vec2::ZERO);
    Single->setScale(0.5);

    cocos2d::Label* Multi = newLabel("10x Summons");
    Multi->setPosition(300, 440);
    Multi->setAnchorPoint(Vec2::ZERO);
    Multi->setScale(0.5);

    _banner = Sprite::create("Button/Rectangle.png");
    _banner->setAnchorPoint(Vec2::ZERO);
    _banner->setPosition(100, 500);
    _banner->setScale(0.3);

    //Here until Background is added
    _back = Sprite::create("Button/Rectangle.png");
    _back->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _back->setPosition(0, 945);
    _back->setScale(0.12);

    Button* backButton = newButton("", "Button/Back.png");
    backButton->setPosition(cocos2d::Vec2(0, 942));
    backButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    backButton->setScale(0.08);

    Button* singleButton = newButton("", "Button/Rectangle.png");
    singleButton->setPosition(cocos2d::Vec2(120, 425));
    singleButton->setAnchorPoint(Vec2::ZERO);
    singleButton->setScale(0.08);

    Button* MultiButton = newButton("", "Button/Rectangle.png");
    MultiButton->setPosition(cocos2d::Vec2(300, 425));
    MultiButton->setAnchorPoint(Vec2::ZERO);
    MultiButton->setScale(0.08);

    backButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
            }
        }
    );

    singleButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                //add single summon pulls
            }
        }
    );

    MultiButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                //add multi summon pulls
            }
        }
    );

    this->addChild(_back);
    this->addChild(_banner);

    
    return true;
}


void SummonMenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}