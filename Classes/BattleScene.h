#pragma once

#include "MainScene.h"
#include "Player.h"
class BattleScene : public MainScene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    Player* player;
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(BattleScene);
};