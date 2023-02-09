#include "RaidMenuScene.h"
USING_NS_CC;

Scene* RaidMenuScene::createScene()
{
    return RaidMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool RaidMenuScene::init()
{
    //////////////////////////////
    // 1. super init _firstRaid
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    Menu();
    Levels();


    //auto bg = newButton("BattleScene.png");
    //bg->setPosition(0, 0);
    //bg->setScale(0.5, 0.5);
    //this->addChild(bg);

    return true;
}



void RaidMenuScene::Menu()
{
    Title = newLabel("RAIDS");
    Title->setPosition(centerWidth(),900);
    this->addChild(Title,1);

    _firstRaid = newButton("", "Rectangle.png");
    _firstRaid->setPosition(cocos2d::Vec2(centerWidth(), 700));
    _firstRaid->setScale(0.4, 0.25);
    this->addChild(_firstRaid);

    Forest = newLabel("Forest");
    Forest->setPosition(centerWidth(), 700);
    this->addChild(Forest, 1);

    Second = newButton("", "Rectangle.png");
    Second->setPosition(cocos2d::Vec2(centerWidth(), 500));
    Second->setScale(0.4, 0.25);
    this->addChild(Second);

    Dungeon = newLabel("Dungeon");
    Dungeon->setPosition(centerWidth(), 500);
    this->addChild(Dungeon, 1);

    Third = newButton("", "Rectangle.png");
    Third->setPosition(cocos2d::Vec2(centerWidth(), 300));
    Third->setScale(0.4, 0.25);
    this->addChild(Third);

    Cave = newLabel("Cave");
    Cave->setPosition(centerWidth(), 300);
    this->addChild(Cave, 1);

    Return = newButton("Return.png");
    Return->setPosition(cocos2d::Vec2(50, 18));
    Return->setScale(0.25, 0.25);
    this->addChild(Return);
}

void RaidMenuScene::Levels()
{
    _firstRaid->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                clean();
            }
        }
    );   
    Second->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());  // Leann's raid menu
            }
        }
    );  
    Third->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());  // Leann's raid menu
            }
        }
    );  
    Return->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());  // Leann's raid menu
            }
        }
    );
}



void RaidMenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}