#pragma once
#include "MainScene.h"
#include "MainMenuScene.h"
#include "AudioEngine.h"


class TitleScreen : public MainScene
{
private:
    float musicVol;
    unsigned int audioID;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    bool onTouchBegan(Touch*, Event*);

    virtual void update(float) override;
    void setBackground();
    void Sounds();

    // implement the "static create()" method manually
    CREATE_FUNC(TitleScreen);
};