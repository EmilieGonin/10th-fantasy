#pragma once
#include "MainScene.h"
#include "Player.h"
#include "MainMenuScene.h"

class TitleScreen : public MainScene
{
public:
    Player* player;
    static cocos2d::Scene* createScene();
    virtual bool init();
    bool onTouchBegan(Touch*, Event*);

    // implement the "static create()" method manually
    CREATE_FUNC(TitleScreen);
};