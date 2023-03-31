#pragma once
#include "MainScene.h"
#include "Interface.h"
#include "BattleScene.h"
#include "MainMenuScene.h"
#include "cocos2d.h"
#include <iostream>

class CharacterMenu : public MainScene, Interface
{
protected:
    //Use interface wrapper instead !
    Button* _firstRaid;
    Button* Return;

    Sprite* bg;
    Sprite* Ring;
    Sprite* Necklace;
    Sprite* Helmet;
    Sprite* Boots;
    Sprite* Chest;
    Sprite* Earring;
    Sprite* Weapon;
    Sprite* Player;
    Sprite* Gem;
    Sprite* Stats;
    Sprite* FirstSup;
    Sprite* SeconSup;

    cocos2d::Label* Title;
    cocos2d::Label* LvlUp;
    cocos2d::Label* Price;

    cocos2d::Vec2 _mousePosition;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void Stuff();
    void Stat();
    void Supports();

    // implement the "static create()" method manually
    CREATE_FUNC(CharacterMenu);
};
