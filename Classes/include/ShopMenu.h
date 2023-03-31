#pragma once
#include "MainScene.h"
#include "Interface.h"
#include "BattleScene.h"
#include "MainMenuScene.h"
#include "cocos2d.h"
#include <iostream>

class ShopMenu : public MainScene
{
protected:
    //Use interface wrapper instead !
    Button* Packsbtn;
    Button* Monneybtn;
    Button* Otherbtn;
    Button* FirstPull;
    Button* SecondPull;
    Button* Return;

    cocos2d::Label* Title;
    cocos2d::Label* Packs;
    cocos2d::Label* Monney;
    cocos2d::Label* Other;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void Menu();
    void PackPage();
    void MonneyPage();
    void OtherPage();
    void SceneChanger();

    // implement the "static create()" method manually
    CREATE_FUNC(ShopMenu);
};