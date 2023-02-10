#include "MainMenuScene.h"
#include "BattleScene.h"
#include "RaidMenuScene.h"
#include "SummonMenuScene.h"
#include "CharacterMenu.h"

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

    _player = Sprite::create("Sprite/remnant_violet.png");
    _player->setPosition(center());
    _player->setScale(0.69);

    this->addChild(_background);
    this->addChild(_player, 1);

    setScene(this);

    Button* raidButton = newButton("", "Button/Battle.png");
    raidButton->setPosition(cocos2d::Vec2(440,25));
    raidButton->setAnchorPoint(Vec2::ZERO);
    raidButton->setScale(0.15);

    raidButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(RaidMenuScene::create());  // Leann's raid menu
            }
        }
    );

    Button* summonButton = newButton("", "Button/Summon.png");
    summonButton->setPosition(cocos2d::Vec2(40, 23));
    summonButton->setAnchorPoint(Vec2::ZERO);
    summonButton->setScale(0.185);

    summonButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(SummonMenuScene::create());
            }
        }
    );   

    Button* characterButton = newButton("", "Button/characterbtn.png");
    characterButton->setPosition(cocos2d::Vec2(5, 860));
    characterButton->setAnchorPoint(Vec2::ZERO);
    characterButton->setScale(0.7);

    characterButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(CharacterMenu::create());
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
