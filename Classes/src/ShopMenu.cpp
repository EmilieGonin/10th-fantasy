#include "ShopMenu.h"
USING_NS_CC;

Scene* ShopMenu::createScene()
{
    return ShopMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool ShopMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Menu();

    return true;
}

void ShopMenu::Menu()
{
    Title = newLabel("SHOP");
    Title->setPosition(centerWidth(), 900);
    this->addChild(Title, 1);


    Packs = newButton("", "Rectangle.png");
    Packs->setPosition(cocos2d::Vec2(centerWidth(), 700));
    Packs->setScale(0.35, 0.3);
    this->addChild(Packs, 1);

    Monney = newButton("", "Rectangle.png");
    Monney->setPosition(cocos2d::Vec2(centerWidth(), centerHeight()));
    Monney->setScale(0.35, 0.3);
    this->addChild(Monney, 1);

    Other = newButton("", "Rectangle.png");
    Other->setPosition(cocos2d::Vec2(centerWidth(), 250));
    Other->setScale(0.35, 0.3);
    this->addChild(Other, 1);


    Return = newButton("", "return.png");
    Return->setPosition(cocos2d::Vec2(50, 18));
    Return->setScale(0.25, 0.25);
    this->addChild(Return, 1);

    Return->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED)
            {
                cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());  // Leann's raid menu
            }
        }
    );
}



void ShopMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
