#pragma once


#include "MainScene.h"
#include "Player.h"
#include "cocos2d.h"
#include "Battle.h"
#include "Entity.h"
#include "GameManager.h"
#include "Database.h"
#include <iostream>
#include <vector>

class RaidBossLootScene : public MainScene
{
private:
    //Battle* battle;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void dropLoot();
    CREATE_FUNC(RaidBossLootScene);

};