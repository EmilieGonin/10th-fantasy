#pragma once
#include "MainScene.h"
#include "Interface.h"
#include "cocos2d.h"
#include <iostream>

class RaidMenuScene : public MainScene, public Interface
{
protected:
    cocos2d::Sprite* _firstRaid;
    cocos2d::Sprite* Second;
    cocos2d::Sprite* Third;
    cocos2d::Sprite* Return;
    cocos2d::Label* Title;
    cocos2d::Label* Forest;
    cocos2d::Label* Cave;
    cocos2d::Label* Dungeon;
    cocos2d::Vec2 _mousePosition;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    bool isTouched(cocos2d::Sprite*);
    void Menu();
    //void SceneChanger();
    void MouseUp(cocos2d::Event* event);
    //void Levels(cocos2d::Event* event);
    void handleEvent(cocos2d::Event* event);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(RaidMenuScene);
};