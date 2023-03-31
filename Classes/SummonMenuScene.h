#pragma once
#include "MainScene.h"

class SummonMenuScene : public MainScene, Interface
{
private:
    //Use interface wrapper instead !
    Sprite* _banner;
    Sprite* _back;

    std::vector<Sprite*> _pulledSprites;
    Button* _button;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    void Buttons();
    void Sprites();
    void Labels();

    void pullResult();
    void cleanSummon();

    // implement the "static create()" method manually
    CREATE_FUNC(SummonMenuScene);
};