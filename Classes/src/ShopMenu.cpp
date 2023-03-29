#include "ShopMenu.h"
USING_NS_CC;

Scene* ShopMenu::createScene()
{
    return ShopMenu::create();
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
    SceneChanger();

    return true;
}

void ShopMenu::Menu()
{
    Title = newLabel("SHOP");
    Title->setPosition(centerWidth(), 900);
    this->addChild(Title, 1);

    Packs = newLabel("Packs");
    Packs->setPosition(centerWidth(), 700);
    this->addChild(Packs, 1);

    Packsbtn = newButton("", "Rectangle.png",1);
    Packsbtn->setPosition(cocos2d::Vec2(centerWidth(), 700));
    Packsbtn->setScale(0.35, 0.3);
    this->addChild(Packsbtn);

    Monney = newLabel("Monney");
    Monney->setPosition(centerWidth(), centerHeight());
    this->addChild(Monney, 1);

    Monneybtn = newButton("", "Rectangle.png", 1);
    Monneybtn->setPosition(cocos2d::Vec2(centerWidth(), centerHeight()));
    Monneybtn->setScale(0.35, 0.3);
    this->addChild(Monneybtn);

    Other = newLabel("Other");
    Other->setPosition(centerWidth(), 250);
    this->addChild(Other, 1);

    Otherbtn = newButton("", "Rectangle.png", 1);
    Otherbtn->setPosition(cocos2d::Vec2(centerWidth(), 250));
    Otherbtn->setScale(0.35, 0.3);
    this->addChild(Otherbtn);


    Return = newButton("", "return.png");
    Return->setPosition(cocos2d::Vec2(50, 18));
    Return->setScale(0.25, 0.25);
    this->addChild(Return, 1);
}

void ShopMenu::PackPage()
{
    Title = newLabel("PACKS SHOP");
    Title->setPosition(centerWidth(), 900);

    Packs = newLabel("Pack 1",1);
    Packs->setPosition(centerWidth(), 600);

    Packsbtn = newButton("", "Rectangle.png");
    Packsbtn->setPosition(cocos2d::Vec2(centerWidth(), 600));
    Packsbtn->setScale(0.35, 0.3);

    Packs = newLabel("Pack 2", 1);
    Packs->setPosition(centerWidth(), centerHeight());

    Monneybtn = newButton("", "Rectangle.png");
    Monneybtn->setPosition(cocos2d::Vec2(centerWidth(), centerHeight()));
    Monneybtn->setScale(0.35, 0.3);

    Other = newLabel("Pack 3", 1);
    Other->setPosition(centerWidth(), 300);

    Otherbtn = newButton("", "Rectangle.png");
    Otherbtn->setPosition(cocos2d::Vec2(centerWidth(), 300));
    Otherbtn->setScale(0.35, 0.3);


    Return = newButton("", "return.png");
    Return->setPosition(cocos2d::Vec2(50, 18));
    Return->setScale(0.25, 0.25);

    Return->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(ShopMenu::create());
            }
        }
    );
}

void ShopMenu::MonneyPage()
{
    Title = newLabel("SHOP");
    Title->setPosition(centerWidth(), 900);


    Packsbtn = newButton("", "Rectangle.png", 1);
    Packsbtn->setPosition(cocos2d::Vec2(centerWidth(), 700));
    Packsbtn->setScale(0.35, 0.3);

    Monneybtn = newButton("", "Rectangle.png", 1);
    Monneybtn->setPosition(cocos2d::Vec2(centerWidth(), centerHeight()));
    Monneybtn->setScale(0.35, 0.3);

    Otherbtn = newButton("", "Rectangle.png", 1);
    Otherbtn->setPosition(cocos2d::Vec2(centerWidth(), 250));
    Otherbtn->setScale(0.35, 0.3);

    Return = newButton("", "return.png");
    Return->setPosition(cocos2d::Vec2(50, 18));
    Return->setScale(0.25, 0.25);

    Return->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(ShopMenu::create());
            }
        }
    );
}

void ShopMenu::OtherPage()
{
    Title = newLabel("SHOP");
    Title->setPosition(centerWidth(), 900);


    Packsbtn = newButton("", "Rectangle.png", 1);
    Packsbtn->setPosition(cocos2d::Vec2(centerWidth(), 700));
    Packsbtn->setScale(0.35, 0.3);

    Monneybtn = newButton("", "Rectangle.png", 1);
    Monneybtn->setPosition(cocos2d::Vec2(centerWidth(), centerHeight()));
    Monneybtn->setScale(0.35, 0.3);

    Otherbtn = newButton("", "Rectangle.png", 1);
    Otherbtn->setPosition(cocos2d::Vec2(centerWidth(), 250));
    Otherbtn->setScale(0.35, 0.3);


    Return = newButton("", "return.png");
    Return->setPosition(cocos2d::Vec2(50, 18));
    Return->setScale(0.25, 0.25);

    Return->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(ShopMenu::create());
            }
        }
    );
}

void ShopMenu::SceneChanger()
{
    setScene(this);
    Packsbtn->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                clean();
                PackPage();
            }
        }
    );
    Monneybtn->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                clean();
                MonneyPage();
            }
        }
    );
    Otherbtn->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                clean();
                OtherPage();
            }
        }
    );
    Return->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
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
