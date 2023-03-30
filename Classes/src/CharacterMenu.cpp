#include "BattleScene.h"
#include "cocos2d.h"
#include "CharacterMenu.h"
USING_NS_CC;

Scene* CharacterMenu::createScene()
{
    return CharacterMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool CharacterMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    bg = newSprite("Background/characterbg.png");
    bg->setPosition(centerWidth(), centerHeight());
    bg->setScale(3);

    Player = newSprite("Sprite/player.png");
    Player->setPosition(200,600);
    
    Player->setScale(2.5);
    
    this->addChild(bg);
    this->addChild(Player, 1);
    Supports();
    Stuff();
    Stat();
    return true;
}

void CharacterMenu::Stuff()
{
    Title = newLabel("STUFF");
    Title->setPosition(centerWidth(), 900);
    this->addChild(Title, 1);


    Helmet = newSprite("Stuff/helmet.png");
    Helmet->setPosition(100, 650);
    Helmet->setScale(0.15, 0.15);
    this->addChild(Helmet, 1);


    Chest = newSprite("Stuff/chest.png");
    Chest->setPosition(100, 550);
    Chest->setScale(0.15, 0.15);
    this->addChild(Chest, 1); 
    
    Boots = newSprite("Stuff/boots.png");
    Boots->setPosition(100, 400);
    Boots->setScale(0.15, 0.15);
    this->addChild(Boots, 1);

    Weapon = newSprite("Stuff/chest.png");
    Weapon->setPosition(100, 300);
    Weapon->setScale(0.2, 0.2);
    this->addChild(Weapon, 1);

    Earring = newSprite("Stuff/earring.png");
    Earring->setPosition(450, 650);
    Earring->setScale(0.15, 0.15);
    this->addChild(Earring, 1); 

    Necklace = newSprite("Stuff/necklace.png");
    Necklace->setPosition(450, 550);
    Necklace->setScale(0.15, 0.15);
    this->addChild(Necklace, 1);

    Ring = newSprite("Stuff/ring.png");
    Ring->setPosition(450, 400);
    Ring->setScale(0.15, 0.15);
    this->addChild(Ring, 1);

    //Gem = newSprite("Stuff/necklace.png");
    //Gem->setPosition(450, 300);
    //Gem->setScale(0.1, 0.1);
    //this->addChild(Gem, 1);

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

void CharacterMenu::Stat()
{

    Title = newLabel("STATS");
    Title->setPosition(centerWidth(), 190);
    this->addChild(Title, 2);  
    
    LvlUp = newLabel("Level Up");
    LvlUp->setPosition(130, 120);
    this->addChild(LvlUp, 2);
    
    Price = newLabel("Price");
    Price->setPosition(400, 120);
    this->addChild(Price, 2);

    Ring = newSprite("Rectangle.png");
    Ring->setPosition(centerWidth(), 150);
    Ring->setScale(0.4, 0.3);
    this->addChild(Ring, 1);
}

void CharacterMenu::Supports()
{
    FirstSup = newSprite("Supports/djeamy.png");
    FirstSup->setPosition(100, 780);
    FirstSup->setScale(0.1, 0.1);
    this->addChild(FirstSup, 1);

    SeconSup = newSprite("Supports/elf.png");
    SeconSup->setPosition(450, 780);
    SeconSup->setScale(0.1, 0.1);
    this->addChild(SeconSup, 1);
}


void CharacterMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
