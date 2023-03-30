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
    
    Button* PeacefulPlay;
    Button* EasyPlay;
    Button* NormalPlay;
    Button* HardPlay;
    Button* InsanePlay;
    Button* UltimatePlay;

    Sprite* PeacefulImg;
    Sprite* EasyImg;
    Sprite* NormalImg;
    Sprite* HardImg;
    Sprite* InsaneImg;
    Sprite* UltimateImg;

    cocos2d::Label* Title;
    cocos2d::Label* Forest;
    cocos2d::Label* Cave;
    cocos2d::Label* Dungeon; 
    
    cocos2d::Label* Peaceful;
    cocos2d::Label* Easy;
    cocos2d::Label* Normal;
    cocos2d::Label* Hard;
    cocos2d::Label* Insane;
    cocos2d::Label* Ultimate;

    struct Difficulty {
        int level;
        int energy;
    };

    Difficulty _difficulties[6];

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void Menu();
    void Level();
    void SceneChanger();
    void Play();
    void loadBattle(int);

    GameManager* _gameManager;

    // implement the "static create()" method manually
    CREATE_FUNC(RaidMenuScene);
};