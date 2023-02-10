#include "MainMenuScene.h"
#include "BattleScene.h"
#include "RaidMenuScene.h"
#include "SummonMenuScene.h"
#include "Database.h"

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

    _database = Database::Instance();

    _background = Sprite::create("BattleScene.png");
    _background->setPosition(0, 0);
    _background->setScale(0.5);
    _background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

    //here temporarely until replacement is found
    _background2 = Sprite::create("Button/Rectangle.png");
    _background2->setPosition(0, 0);
    _background2->setScale(0.28);
    _background2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _background3 = Sprite::create("Button/Rectangle.png");
    _background3->setPosition(260, 0);
    _background3->setScale(0.28);
    _background3->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    

    _player = Sprite::create("Sprite/remnant_violet.png");
    _player->setPosition(center());
    _player->setScale(0.69);

    this->addChild(_background);
    this->addChild(_background2, 2);
    this->addChild(_background3, 2);
    this->addChild(_player, 1);

    setScene(this);

    Button* raidButton = newButton("", "Button/Battle.png", 3);
    raidButton->setPosition(cocos2d::Vec2(420,30));
    raidButton->setAnchorPoint(Vec2::ZERO);
    raidButton->setScale(0.15);

    raidButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(RaidMenuScene::create());  // Leann's raid menu
            }
        }
    );

    Button* summonButton = newButton("", "Button/Summon.png", 3);
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

    Button* profileButton = newButton("", "Button/Profile.png", 2);
    profileButton->setPosition(cocos2d::Vec2(0, 945));
    profileButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    profileButton->setScale(0.12);

    profileButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                Button* backButton = newButton("", "Button/Back.png", 5);
                backButton->setPosition(cocos2d::Vec2(100, 850));
                backButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
                backButton->setScale(0.03);
                backButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
                    {
                        if (type == Widget::TouchEventType::ENDED) {
                            cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
                        }
                    }
                );

                username = "Username: " + _database->user()->name;

                cocos2d::Label* user = newLabel(username, 5);
                user->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
                user->setScale(0.8);
                user->setPosition(125, 800);

                _background4 = Sprite::create("Button/Rectangle.png");
                _background4->setPosition(100, 850);
                _background4->setScale(0.25);
                _background4->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
                this->addChild(_background4, 4);
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
