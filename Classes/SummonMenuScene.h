#pragma once
#include "MainScene.h"

class SummonMenuScene : public MainScene, Interface
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    Sprite* _banner;
    Sprite* _back;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(SummonMenuScene);
};