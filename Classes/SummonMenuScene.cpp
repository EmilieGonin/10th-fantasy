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
    _database = Database::Instance();
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
                pullResult();
            }
        }
    );

    MultiButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                pull(10);
                pullResult();
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

void SummonMenuScene::pullResult() {
    if (_button != nullptr) {
        cleanSummon();
    }

    int width = 0;
    int height = 0;
    int count = 1;

    for (size_t i = 0; i < _database->lastPull()->size(); i++)
    {
        std::string name = _database->lastPull()[0][i].name;
        Sprite* sprite = newSprite("Supports/" + name + ".png", 2);
        sprite->setScale(0.15);

        if (_database->lastPull()->size() == 1) {
            sprite->setPosition(Vec2(centerWidth(), centerHeight() + 170));
        }
        else {
            if (count == 3) {
                height += 160;
                width = 0;
                count = 1;
            }

            sprite->setPosition((160 * width) + 180, centerHeight() + 350 - height);

            width++;
            count++;
        }

        _pulledSprites.push_back(sprite);
    }

    _button = newButton("OK");

    if (_database->lastPull()->size() == 1) {
        _button->setPosition(Vec2(centerWidth(), 550));
    }
    else {
        _button->setPosition(Vec2(centerWidth(), 50));
    }

    _button->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cleanSummon();
            }
        }
    );
}

void SummonMenuScene::cleanSummon() {
    for (Sprite* item : _pulledSprites) {
        this->removeChild(item);
    }
    _pulledSprites.clear();
    this->removeChild(_button);
}