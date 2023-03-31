#include "RaidBossLootScene.h"
USING_NS_CC;

Scene* RaidBossLootScene::createScene()
{
    return RaidBossLootScene::create();
}



bool RaidBossLootScene::init()
{
    if (!Scene::init()) { return false; }
 

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    return true;
}

void RaidBossLootScene::dropLoot()
{
    //if (battle->getWin() == true)
    //{
    //    clean();
    //}
}
