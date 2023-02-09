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


    EventListenerMouse* listener = EventListenerMouse::create();
    listener->onMouseUp = CC_CALLBACK_1(RaidMenuScene::MouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    Menu();

    //auto bg = newSprite("BattleScene.png");
    //bg->setPosition(0, 0);
    //bg->setScale(0.5, 0.5);
    //this->addChild(bg);

    return true;
}
void RaidMenuScene::handleEvent(Event* event) {
    EventMouse* e = (EventMouse*)event;
    _mousePosition = e->getLocationInView();

    if (isTouched(Return))
    {
        auto scene = RaidMenuScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
    else if (isTouched(_firstRaid))
    {
        clean();
    }
    else if (isTouched(Second))
    {
        auto scene = RaidMenuScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
    else if (isTouched(Third))
    {
        auto scene = RaidMenuScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}



void RaidMenuScene::Menu()
{
    Title = newLabel("RAIDS");
    Title->setPosition(centerWidth(),900);
    this->addChild(Title,1);

    auto _firstRaid = newSprite("Rectangle.png");
    _firstRaid->setPosition(centerWidth(), 700);
    _firstRaid->setScale(0.4, 0.25);
    this->addChild(_firstRaid);

   /* Forest = newLabel("Forest");
    Forest->setPosition(centerWidth(), 700);
    this->addChild(Forest, 1);*/

   auto Second = newSprite("Rectangle.png");
    Second->setPosition(centerWidth(), 500);
    Second->setScale(0.4, 0.25);
    this->addChild(Second);

    Dungeon = newLabel("Dungeon");
    Dungeon->setPosition(centerWidth(), 500);
    this->addChild(Dungeon, 1);

    auto Third = newSprite("Rectangle.png");
    Third->setPosition(centerWidth(), 300);
    Third->setScale(0.4, 0.25);
    this->addChild(Third);

    Cave = newLabel("Cave");
    Cave->setPosition(centerWidth(), 300);
    this->addChild(Cave, 1);

    auto Return = newSprite("Return.png");
    Return->setPosition(50, 18);
    Return->setScale(0.25, 0.25);
    this->addChild(Return);
}



//void RaidMenuScene::SceneChanger()
//{
//    if (isTouched(Return)) 
//    {
//        auto scene = RaidMenuScene::createScene();
//        Director::getInstance()->replaceScene(scene);
//    }   
//    else if (isTouched(_firstRaid))
//    {
//        clean();
//    }
//    else if (isTouched(Second))
//    {
//        auto scene = RaidMenuScene::createScene();
//        Director::getInstance()->replaceScene(scene);
//    } 
//    else if (isTouched(Third))
//    {
//        auto scene = RaidMenuScene::createScene();
//        Director::getInstance()->replaceScene(scene);
//    }
//}

//void RaidMenuScene::Levels(Event* event)
//{
//    auto label = newLabel("RAIDS", "fonts/Marker Felt.ttf", 24);
//    label->setPosition(240, 290);
//    this->addChild(label, 1);
//
//    auto _firstRaid = newSprite("Rectangle.png");
//    _firstRaid->setPosition(240, 230);
//    _firstRaid->setScale(0.15, 0.1);
//    this->addChild(_firstRaid);
//
//    auto Forest = newLabel("Forest", "fonts/Marker Felt.ttf", 24);
//    Forest->setPosition(240, 230);
//    this->addChild(Forest, 1);
//
//    auto Second = newSprite("Rectangle.png");
//    Second->setPosition(240, 150);
//    Second->setScale(0.15, 0.1);
//    this->addChild(Second);
//
//    auto Dungeon = newLabel("Dungeon", "fonts/Marker Felt.ttf", 24);
//    Dungeon->setPosition(240, 150);
//    this->addChild(Dungeon, 1);
//
//    auto Third = newSprite("Rectangle.png");
//    Third->setPosition(240, 70);
//    Third->setScale(0.15, 0.1);
//    this->addChild(Third);
//
//    auto Cave = newLabel("Cave", "fonts/Marker Felt.ttf", 24);
//    Cave->setPosition(240, 70);
//    this->addChild(Cave, 1);
//
//    auto Return = newSprite("Return.png");
//    Return->setPosition(160, 15);
//    Return->setScale(0.1, 0.1);
//    this->addChild(Return);
//}

bool RaidMenuScene::isTouched(Sprite* sprite) {
    Rect bounds = sprite->getBoundingBox();

    if (bounds.containsPoint(_mousePosition)) {
        return true;
    }
    else {
        return false;
    }
}

void RaidMenuScene::MouseUp(cocos2d::Event* event)
{
    handleEvent(event);

}

void RaidMenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}