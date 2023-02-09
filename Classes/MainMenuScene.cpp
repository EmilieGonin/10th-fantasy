#include "MainMenuScene.h"
#include "BattleScene.h"
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    _background = Sprite::create("BattleScene.png");
    _background->setPosition(0, 0);
    _background->setScale(0.5);
    _background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

    _battle = Sprite::create("Sprite/Battle.png");
    _battle->setAnchorPoint(Vec2::ZERO);
    _battle->setScale(0.15);
    _battle->setPosition(440, 25);


    //MouseEvents
    EventListenerMouse* listener = EventListenerMouse::create();
    listener->onMouseUp = CC_CALLBACK_1(MainMenuScene::MouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    this->addChild(_background);
    this->addChild(_battle, 3);

    setScene(this);

    Button* button = newButton("next");
    //button->loadTextureNormal("Sprite/Battle.png");
    button->setPosition(cocos2d::Vec2(centerWidth(), centerHeight() - 100));

    button->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(BattleScene::create());
            }
        }
    );

    return true;
}


void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
