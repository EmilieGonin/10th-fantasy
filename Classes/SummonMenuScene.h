#pragma once
#include "MainScene.h"

class SummonMenuScene : public MainScene, Interface
{
private:
    //Use interface wrapper instead !
    Sprite* _banner;
    Sprite* _back;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();


    Sprite* _banner;
    Sprite* _back;

    void Buttons();
    void Sprites();
    void Labels();

    // implement the "static create()" method manually
    CREATE_FUNC(SummonMenuScene);
};