#include "TitleScreen.h"
USING_NS_CC;

Scene* TitleScreen::createScene()
{
    return TitleScreen::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool TitleScreen::init()
{
    if (!Scene::init()) { return false; }

    _database->init(this);
    setScene(this);

    //Touch screen event
    if (_database->isLogged()) {
        EventListenerTouchOneByOne* touchListener = EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan = CC_CALLBACK_2(TitleScreen::onTouchBegan, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    }

    Sprite* sprite = newSprite("Supports/djeamy.png", -1);
    sprite->setPosition(center());
    sprite->setOpacity(120);

    return true;
}

bool TitleScreen::onTouchBegan(Touch* touch, Event* event) {
    _director->replaceScene(MainMenuScene::create());
    return true;
}