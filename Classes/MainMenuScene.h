#pragma once
#include "MainScene.h"
#include <iostream>

class MainMenuScene : public MainScene, Interface
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    bool openSubMenus;
    bool openInventory;

    Database* _database;

    Sprite* _player;
    Sprite* _background;
    Sprite* _background2;
    Sprite* _background3;
    Sprite* _background4;
    Sprite* _dropDownMenu;
    Sprite* _inventory;
    Sprite* _settings;
    std::string username;

    float musicVol;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void Buttons();
    void Sprites();
    void Labels();
    void BackButton(int, int, float, int);
    void Account();
    void OpenInventory();
    void Settings();
    void Sounds();


    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
};