#include "RaidMenuScene.h"
#include "GameManager.h"
USING_NS_CC;

Scene* RaidMenuScene::createScene()
{
    return RaidMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool RaidMenuScene::init()
{
     
    // 1. super init _firstRaid
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _gameManager = GameManager::Instance();
    Menu();
    SceneChanger();


    //auto bg = newButton("BattleScene.png");
    //bg->setPosition(0, 0);
    //bg->setScale(0.5, 0.5);
    //this->addChild(bg);

    return true;
}



void RaidMenuScene::Menu()
{
    Title = newLabel("RAIDS", 1);
    Title->setPosition(centerWidth(),900);
    this->addChild(Title,1);


    _firstRaid = newButton("", "Sprite/Betala.png", 1);
    _firstRaid->setPosition(cocos2d::Vec2(centerWidth(), 700));
    _firstRaid->setScale(0.4, 0.4);
    this->addChild(_firstRaid, 1);

    Second = newButton("", "Sprite/Shado.png", 1);
    Second->setPosition(cocos2d::Vec2(centerWidth(), 500));
    Second->setScale(0.4, 0.4);
    this->addChild(Second, 1);

    Third = newButton("", "Sprite/Laijande.png", 1);
    Third->setPosition(cocos2d::Vec2(centerWidth(), 300));
    Third->setScale(0.4, 0.4);
    this->addChild(Third, 1);

    Return = newButton("", "Return.png", 1);
    Return->setPosition(cocos2d::Vec2(50, 18));
    Return->setScale(0.25, 0.25);
    this->addChild(Return, 1);

}

void RaidMenuScene::Level()
{
    // LEVELS LABELS 
    Title = newLabel("FOREST RAID", 1);
    Title->setPosition(centerWidth(), 900);

    Peaceful = newLabel("Peaceful", 1);
    Peaceful->setPosition(150, 780);
    Peaceful->setLocalZOrder(1);

    Easy = newLabel("Easy", 1);
    Easy->setPosition(120, 650);
    Easy->setLocalZOrder(1);

    Normal = newLabel("Normal", 1);
    Normal->setPosition(130, 520);
    Normal->setLocalZOrder(1);    

    Hard = newLabel("Hard", 1);
    Hard->setPosition(120, 390);
    Hard->setLocalZOrder(1);

    Insane = newLabel("Insane", 1);
    Insane->setPosition(130, 260);
    Insane->setLocalZOrder(1); 
    
    Ultimate = newLabel("Ultimate", 1);
    Ultimate->setPosition(140, 130);
    Ultimate->setLocalZOrder(1);


    // LEVELS SPRITE
    PeacefulImg = newSprite("Sprite/DifficultyBetala.png");
    PeacefulImg->setPosition(cocos2d::Vec2(centerWidth(), 780));
    PeacefulImg->setScale(0.4, 0.4);

    EasyImg = newSprite("Sprite/DifficultyBetala.png");
    EasyImg->setPosition(cocos2d::Vec2(centerWidth(), 650));
    EasyImg->setScale(0.4, 0.4);

    NormalImg = newSprite("Sprite/DifficultyBetala.png");
    NormalImg->setPosition(cocos2d::Vec2(centerWidth(), 520));
    NormalImg->setScale(0.4, 0.4);
    
    HardImg = newSprite("Sprite/DifficultyBetala.png");
    HardImg->setPosition(cocos2d::Vec2(centerWidth(), 390));
    HardImg->setScale(0.4, 0.4);
    
    InsaneImg = newSprite("Sprite/DifficultyBetala.png");
    InsaneImg->setPosition(cocos2d::Vec2(centerWidth(), 260));
    InsaneImg->setScale(0.4, 0.4);
    
    UltimateImg = newSprite("Sprite/DifficultyBetala.png");
    UltimateImg->setPosition(cocos2d::Vec2(centerWidth(), 130));
    UltimateImg->setScale(0.4, 0.4);

    // LEVEL BUTTON

    PeacefulPlay = newButton("", "Button/playbtn.png", 1);
    PeacefulPlay->setPosition(cocos2d::Vec2(400, 780));
    PeacefulPlay->setScale(0.05, 0.05);

    EasyPlay = newButton("", "Button/playbtn.png", 1);
    EasyPlay->setPosition(cocos2d::Vec2(400, 650));
    EasyPlay->setScale(0.05, 0.05);

    NormalPlay = newButton("", "Button/playbtn.png", 1);
    NormalPlay->setPosition(cocos2d::Vec2(400, 520));
    NormalPlay->setScale(0.05, 0.05);

    HardPlay = newButton("", "Button/playbtn.png", 1);
    HardPlay->setPosition(cocos2d::Vec2(400, 390));
    HardPlay->setScale(0.05, 0.05);

    InsanePlay = newButton("", "Button/playbtn.png", 1);
    InsanePlay->setPosition(cocos2d::Vec2(400, 260));
    InsanePlay->setScale(0.05, 0.05);

    UltimatePlay = newButton("", "Button/playbtn.png", 1);
    UltimatePlay->setPosition(cocos2d::Vec2(400, 130));
    UltimatePlay->setScale(0.05, 0.05);
    UltimatePlay->setLocalZOrder(1);

    Play();


    Return = newButton("","Return.png", 1);
    Return->setPosition(cocos2d::Vec2(50, 18));
    Return->setScale(0.25, 0.25);

    Return->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(RaidMenuScene::create());
            }
        }
    );
}

void RaidMenuScene::Play()
{
    PeacefulPlay->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                _gameManager->setBossLvl(8);
                cocos2d::Director::getInstance()->replaceScene(BattleScene::create());  // Leann's raid menu
            }
        }
    );   
    
    EasyPlay->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                _gameManager->setBossLvl(18);
                cocos2d::Director::getInstance()->replaceScene(BattleScene::create());  // Leann's raid menu
            }
        }
    );   
    
    NormalPlay->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                _gameManager->setBossLvl(29);
                cocos2d::Director::getInstance()->replaceScene(BattleScene::create());  // Leann's raid menu
            }
        }
    );   
    
    HardPlay->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                _gameManager->setBossLvl(37);
                cocos2d::Director::getInstance()->replaceScene(BattleScene::create());  // Leann's raid menu
            }
        }
    );  
    
    InsanePlay->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                _gameManager->setBossLvl(44);
                cocos2d::Director::getInstance()->replaceScene(BattleScene::create());  // Leann's raid menu
            }
        }
    );   
    
    UltimatePlay->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                _gameManager->setBossLvl(50);
                cocos2d::Director::getInstance()->replaceScene(BattleScene::create());  // Leann's raid menu
            }
        }
    );
}

void RaidMenuScene::SceneChanger()
{
    setScene(this);
    _firstRaid->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                clean();
                _gameManager->setBossId(1);
                Level();
            }
        }
    );   
    Second->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {

                clean();
                _gameManager->setBossId(2);
                Level();
            }
        }
    );  
    Third->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {    
                clean();
                _gameManager->setBossId(3);
                Level();
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



void RaidMenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}