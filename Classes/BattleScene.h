#pragma once

#include "MainScene.h"
#include "Player.h"
#include "cocos2d.h"
#include "Battle.h"
#include "Entity.h"
#include "GameManager.h"
#include <iostream>
#include <vector>

class BattleScene : public MainScene
{
public:
  
    static cocos2d::Scene* createScene();
    std::vector<Enemy*> _enemies;
    virtual bool init();
    Battle* battle;
    Player* player;
    cocos2d::Vec2 _mousePosition;
    CREATE_FUNC(BattleScene);

    void loop(float);

    GameManager* gameManager;

protected:
    void MouseUp(cocos2d::Event*);
};