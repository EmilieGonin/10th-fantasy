#pragma once
#include "MainScene.h"
#include "Interface.h"
#include "BattleScene.h"
#include "MainMenuScene.h"
#include "cocos2d.h"
#include <iostream>

class RaidMenuScene : public MainScene, Interface
{
protected:
    Button* _firstRaid;
    Button* Second;
    Button* Third;
    Button* Return;
    cocos2d::Label* Title;
    cocos2d::Label* Forest;
    cocos2d::Label* Cave;
    cocos2d::Label* Dungeon;
    cocos2d::Vec2 _mousePosition;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void Menu();
    void Levels();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(RaidMenuScene);
};