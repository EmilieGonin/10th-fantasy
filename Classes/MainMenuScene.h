#pragma once
#include "MainScene.h"

class MainMenuScene : public MainScene, Interface
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();


    Sprite* _battle;
    Sprite* _background;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
};