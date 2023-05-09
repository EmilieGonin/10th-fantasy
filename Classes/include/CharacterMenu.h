#pragma once
#include "MainScene.h"
#include "Interface.h"
#include "BattleScene.h"
#include "Player.h"
#include "MainMenuScene.h"
#include "cocos2d.h"
#include <iostream>

class CharacterMenu : public MainScene
{
protected:
    //Use interface wrapper instead !
    Button* _firstRaid;
    Button* Return;
    Player* player;
    Sprite* bg;
    Sprite* popup;
    Sprite* Playerr;
    Sprite* Gem;
    Sprite* Stats;
    Sprite* equipp;

    Button* Ring;
    Button* Necklace;
    Button* Helmet;
    Button* Boots;
    Button* Chest;
    Button* Earring;
    Button* Weapon;
    Button* FirstSup;
    Button* SecondSup;
    Button* backButton;

    cocos2d::Label* Title;
    cocos2d::Label* LvlUp;
    cocos2d::Label* Price;

    cocos2d::Label* stats;
    cocos2d::Label* rarity;

    Sprite* perso;
    Button* upgrade;
    Button* equip;
    Sprite* unequip;
    db::gear stuffToEquip;
    Rect equipBounds;
    Rect desequipBounds;
    std::vector<Sprite*> displayedSprite;
    std::vector<Rect> boundings;
    std::vector< db::gear> allGears;
   
    cocos2d::Vec2 _mousePosition;

    void CharacterMenu::MouseUp(Event*);

public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void Stuff();
    void Stat();
    void Supports();

    void PopupEmpty(int);
    void PopupGear(db::gear);
    void BackButton();

    // a selector callback

    void menuCloseCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(CharacterMenu);
};
