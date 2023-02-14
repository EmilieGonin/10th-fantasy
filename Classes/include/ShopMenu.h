#pragma once
#include "MainScene.h"
#include "Interface.h"
#include "BattleScene.h"
#include "MainMenuScene.h"
#include "cocos2d.h"
#include <iostream>

class ShopMenu : public MainScene, Interface
{
protected:
    Button* Packs;
    Button* Monney;
    Button* Other;

    Button* FirstPull;
    Button* SecondPull;

    Button* Return;



    cocos2d::Label* Title;


public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void Menu();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(ShopMenu);
};