#include "SummonMenuScene.h"
#include "MainMenuScene.h"
USING_NS_CC;

Scene* SummonMenuScene::createScene()
{
    return SummonMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SummonMenuScene::init()
{
    if (!Scene::init()) { return false; }
    setScene(this);

    Sprites();
    Buttons();
    Labels();

    return true;
}

void SummonMenuScene::Sprites() {
    _banner = Sprite::create("Banners/djeamy_banner.png");
    _banner->setAnchorPoint(Vec2::ZERO);
    _banner->setPosition(10, 500);
    _banner->setScale(0.5);

    //Here until Background is added
    _back = Sprite::create("Button/Rectangle.png");
    _back->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _back->setPosition(0, 945);
    _back->setScale(0.12);

    this->addChild(_back);
    this->addChild(_banner);
}

void SummonMenuScene::Buttons() {

    Button* backButton = newButton("", "Button/Back.png", 1);
    backButton->setPosition(cocos2d::Vec2(0, 942));
    backButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    backButton->setScale(0.08);

    Button* singleButton = newButton("", "Button/Rectangle.png", 1);
    singleButton->setPosition(cocos2d::Vec2(120, 425));
    singleButton->setAnchorPoint(Vec2::ZERO);
    singleButton->setScale(0.08);

    Button* MultiButton = newButton("", "Button/Rectangle.png", 1);
    MultiButton->setPosition(cocos2d::Vec2(300, 425));
    MultiButton->setAnchorPoint(Vec2::ZERO);
    MultiButton->setScale(0.08);

    backButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
            }
        }
    );

    singleButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                pull(1);
            }
        }
    );

    MultiButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                pull(10);
            }
        }
    );
}

void SummonMenuScene::Labels() {
    cocos2d::Label* Single = newLabel("Single Summons", 2);
    Single->setPosition(120, 440);
    Single->setAnchorPoint(Vec2::ZERO);
    Single->setScale(0.5);

    cocos2d::Label* Multi = newLabel("10x Summons", 2);
    Multi->setPosition(300, 440);
    Multi->setAnchorPoint(Vec2::ZERO);
    Multi->setScale(0.5);
}