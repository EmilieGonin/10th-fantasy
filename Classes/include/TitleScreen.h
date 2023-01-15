#pragma once
#include "MainScene.h"

class TitleScreen : public MainScene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(TitleScreen);
};