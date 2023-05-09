#pragma once
#include "MainScene.h"
#include "Player.h"
#include <iostream>

class MainMenuScene : public MainScene
{
private:
    Database* _database;
    

    bool openSubMenus;
    bool openInventory;

    int x = 60;
    int maxX = 360;
    float musicVol;
    unsigned int audioID;
    int tag = 0;

    std::string username;
    std::string _energy;
    std::string _crystal;

    //Move sprites to interface wrapper
    Sprite* _player;
    Sprite* _background;
    Sprite* _background2;
    Sprite* _background3;
    Sprite* _background4;
    Sprite* _dropDownMenu;
    Sprite* _inventory;
    Sprite* _settings;
    Sprite* sound;
    Sprite* _textBox;




public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void Buttons();
    void Sprites();
    void Labels();
    void Tuto();
    void newTutoNextButton();
    void BackButton(int, int, float, int);
    void Account();
    void OpenInventory();
    void Settings();
    void Sounds();
    void SoundsRect(int, int);

    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
};