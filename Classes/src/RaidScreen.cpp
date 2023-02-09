#include "RaidScreen.h"
USING_NS_CC;

Scene* RaidScreen::createScene()
{
    return RaidScreen::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool RaidScreen::init()
{
    //////////////////////////////
    // 1. super init _firstRaid
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Menu();

    EventListenerMouse* listener = EventListenerMouse::create();
    listener->onMouseUp = CC_CALLBACK_1(RaidScreen::MouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //auto bg = Sprite::create("BattleScene.png");
    //bg->setPosition(0, 0);
    //bg->setScale(0.5, 0.5);
    //this->addChild(bg);
    One = newLabel("Test");
    One->setPosition(240, 290);
    this->addChild(One);
    return true;
}
void RaidScreen::handleEvent(Event* event) {
    EventMouse* e = (EventMouse*)event;
    _mousePosition = e->getLocationInView();
}

bool RaidScreen::isTouched(Sprite* sprite) {
    Rect bounds = sprite->getBoundingBox();

    if (bounds.containsPoint(_mousePosition)) {
        return true;
    }
    else {
        return false;
    }
}

void RaidScreen::Menu()
{
    auto label = Label::createWithTTF("RAIDS", "fonts/Marker Felt.ttf", 24);
    label->setPosition(240,290);
    this->addChild(label,1);   

    auto _firstRaid = Sprite::create("Rectangle.png");
    _firstRaid->setPosition(240, 230);
    _firstRaid->setScale(0.15, 0.1);
    this->addChild(_firstRaid);

    auto Forest = Label::createWithTTF("Forest", "fonts/Marker Felt.ttf", 24);
    Forest->setPosition(240, 230);
    this->addChild(Forest, 1);

    auto Second = Sprite::create("Rectangle.png");
    Second->setPosition(240, 150);
    Second->setScale(0.15, 0.1);
    this->addChild(Second);

    auto Dungeon = Label::createWithTTF("Dungeon", "fonts/Marker Felt.ttf", 24);
    Dungeon->setPosition(240, 150);
    this->addChild(Dungeon, 1);

    auto Third = Sprite::create("Rectangle.png");
    Third->setPosition(240, 70);
    Third->setScale(0.15, 0.1);
    this->addChild(Third);

    auto Cave = Label::createWithTTF("Cave", "fonts/Marker Felt.ttf", 24);
    Cave->setPosition(240, 70);
    this->addChild(Cave, 1);

    auto Return = Sprite::create("Return.png");
    Return->setPosition(160, 15);
    Return->setScale(0.1, 0.1);
    this->addChild(Return);
}

void RaidScreen::SceneChanger()
{
    if (isTouched(Return)) 
    {
        auto scene = RaidScreen::createScene();
        Director::getInstance()->replaceScene(scene);
    }   
    else if (isTouched(_firstRaid))
    {
    }
    else if (isTouched(Second))
    {
        auto scene = RaidScreen::createScene();
        Director::getInstance()->replaceScene(scene);
    } 
    else if (isTouched(Third))
    {
        auto scene = RaidScreen::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}

void RaidScreen::Levels(Event* event)
{
    auto label = Label::createWithTTF("RAIDS", "fonts/Marker Felt.ttf", 24);
    label->setPosition(240, 290);
    this->addChild(label, 1);

    auto _firstRaid = Sprite::create("Rectangle.png");
    _firstRaid->setPosition(240, 230);
    _firstRaid->setScale(0.15, 0.1);
    this->addChild(_firstRaid);

    auto Forest = Label::createWithTTF("Forest", "fonts/Marker Felt.ttf", 24);
    Forest->setPosition(240, 230);
    this->addChild(Forest, 1);

    auto Second = Sprite::create("Rectangle.png");
    Second->setPosition(240, 150);
    Second->setScale(0.15, 0.1);
    this->addChild(Second);

    auto Dungeon = Label::createWithTTF("Dungeon", "fonts/Marker Felt.ttf", 24);
    Dungeon->setPosition(240, 150);
    this->addChild(Dungeon, 1);

    auto Third = Sprite::create("Rectangle.png");
    Third->setPosition(240, 70);
    Third->setScale(0.15, 0.1);
    this->addChild(Third);

    auto Cave = Label::createWithTTF("Cave", "fonts/Marker Felt.ttf", 24);
    Cave->setPosition(240, 70);
    this->addChild(Cave, 1);

    auto Return = Sprite::create("Return.png");
    Return->setPosition(160, 15);
    Return->setScale(0.1, 0.1);
    this->addChild(Return);
}

void RaidScreen::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}