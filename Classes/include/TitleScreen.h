#pragma once
#include "MainScene.h"
#include "MainMenuScene.h"

class TitleScreen : public MainScene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    bool onTouchBegan(Touch*, Event*);

    virtual void update(float) override;

    // implement the "static create()" method manually
    CREATE_FUNC(TitleScreen);
};