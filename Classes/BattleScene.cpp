#include "BattleScene.h"
#include "cocos2d.h"
#include "Player.h"
USING_NS_CC;

Scene* BattleScene::createScene()
{
    return BattleScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool BattleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    player = new Player();
    cocos2d::Sprite* background = Sprite::create("BattleScene.png");
    background->setPosition(0, 0);
    background->setScale(0.5);
    background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);


    //this->addChild(background);
    this->addChild(player->getSprite());
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    return true;
}
