#pragma once

#include "MainScene.h"
#include "Player.h"
#include "cocos2d.h"
#include "Battle.h"
#include "Entity.h"
#include "GameManager.h"
#include "PlayerManager.h"
#include "Database.h"
#include <iostream>
#include <vector>

class BattleScene : public MainScene
{
private:
    GameManager* gameManager;
    std::vector<Enemy*> _enemies;
    Battle* battle;
    Player* player;
    cocos2d::Vec2 _mousePosition;

protected:
    void MouseUp(cocos2d::Event*);

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(BattleScene);

    void loop(float);
};