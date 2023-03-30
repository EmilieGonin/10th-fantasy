#include "MainMenuScene.h"
#include "BattleScene.h"
#include "RaidMenuScene.h"
#include "SummonMenuScene.h"
#include "CharacterMenu.h"
#include "ShopMenu.h"
//#include "Database.h"


USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    openSubMenus = false;

    setScene(this);

    Sprites();
    Labels();
    Buttons();

    if (!_gameManager->getTutoCompleted()) {
        Tuto();
    }
    return true;
}

void MainMenuScene::Tuto() {
    TutoTextBox(100, 280);
    TutoNextButton();
    if (_gameManager->getTutoPhases() == 0) {
        Interface::newLabel("Hello and welcome to our headquarters! I'll help you make yourself at home.", 100, 450, 5);
    }
    else if (_gameManager->getTutoPhases() == 1) {
        Interface::newLabel("", 0, 0, 5);
    }
    else if (_gameManager->getTutoPhases() == 2) {
        Interface::newLabel("", 0, 0, 5);
    }
    else if (_gameManager->getTutoPhases() == 3) {
        Interface::newLabel("", 0, 0, 5);
    }
    else if (_gameManager->getTutoPhases() == 4) {
        Interface::newLabel("", 0, 0, 5);
    }
}

void MainMenuScene::Sprites() {

    _background = Sprite::create("BattleScene.png");
    _background->setPosition(0, 0);
    _background->setScale(0.5);
    _background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

    //here temporarely until replacement is found
    _background2 = Sprite::create("Button/Rectangle.png");
    _background2->setPosition(0, 0);
    _background2->setScale(0.28);
    _background2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _background3 = Sprite::create("Button/Rectangle.png");
    _background3->setPosition(260, 0);
    _background3->setScale(0.28);
    _background3->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);


    _player = Sprite::create("Sprite/remnant_violet.png");
    _player->setPosition(center());
    _player->setScale(1);

    this->addChild(_background);
    this->addChild(_background2, 2);
    this->addChild(_background3, 2);
    this->addChild(_player, 1);
}

void MainMenuScene::Labels() {
   
}

void MainMenuScene::Buttons() {

    Button* raidButton = newButton("", "Button/battle_button.png", 3);
    raidButton->setPosition(cocos2d::Vec2(420, 30));
    raidButton->setAnchorPoint(Vec2::ZERO);
    raidButton->setScale(0.35);

    raidButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED && openSubMenus == false && _gameManager->getTutoCompleted()) {
                cocos2d::Director::getInstance()->replaceScene(RaidMenuScene::create());  // Leann's raid menu
            }
        }
    );

    Button* shopButton = newButton("", "Button/Shop.png", 3);
    shopButton->setPosition(cocos2d::Vec2(225, 23));
    shopButton->setAnchorPoint(Vec2::ZERO);
    shopButton->setScale(0.25);

    shopButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED && openSubMenus == false && _gameManager->getTutoCompleted()) {
                cocos2d::Director::getInstance()->replaceScene(ShopMenu::create());  // Leann's raid menu
            }
        }
    );

    Button* summonButton = newButton("", "Button/Summon.png", 3);
    summonButton->setPosition(cocos2d::Vec2(40, 23));
    summonButton->setAnchorPoint(Vec2::ZERO);
    summonButton->setScale(0.185);

    summonButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED && openSubMenus == false && _gameManager->getTutoCompleted()) {
                cocos2d::Director::getInstance()->replaceScene(SummonMenuScene::create());
            }
        }
    );   

    Button* characterButton = newButton("", "Button/characterbtn.png");
    characterButton->setPosition(cocos2d::Vec2(150, 860));
    characterButton->setAnchorPoint(Vec2::ZERO);
    characterButton->setScale(0.7);

    characterButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED && _gameManager->getTutoCompleted()) {
                cocos2d::Director::getInstance()->replaceScene(CharacterMenu::create());
            }
        }
    );

    Button* profileButton = newButton("", "Button/Profile.png", 2);
    profileButton->setPosition(cocos2d::Vec2(0, 945));
    profileButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    profileButton->setScale(0.12);

    profileButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED && openSubMenus == false && _gameManager->getTutoCompleted()) {

                openSubMenus = true;

                BackButton(100, 850, 0.03, 5);

                username = "Username: " + _database->user()->name;

                cocos2d::Label* user = newLabel(username, 5);
                user->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
                user->setScale(0.8);
                user->setPosition(125, 800);

                _background4 = Sprite::create("Button/Rectangle.png");
                _background4->setPosition(100, 850);
                _background4->setScale(0.25);
                _background4->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
                this->addChild(_background4, 4);
            }
        }
    );

    Button* dropDownButton = newButton("", "Button/DropDown.png", 2);
    dropDownButton->setPosition(cocos2d::Vec2(540, 880));
    dropDownButton->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    dropDownButton->setScale(0.045);

    dropDownButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED && openSubMenus == false && _gameManager->getTutoCompleted()) {

                OpenInventory();

                _dropDownMenu = Sprite::create("DropDownMenu.png");
                _dropDownMenu->setPosition(540, 880);
                _dropDownMenu->setScale(0.25);
                _dropDownMenu->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
                this->addChild(_dropDownMenu, 3);
            }
        }
    );

    Button* settingsButton = newButton("", "Button/Settings.png", 4);
    settingsButton->setPosition(cocos2d::Vec2(540, 950));
    settingsButton->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    settingsButton->setScale(0.12);

    settingsButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED && openSubMenus == false && _gameManager->getTutoCompleted()) {
                openSubMenus = true;

                BackButton(10, 920, 0.05, 6);

                cocos2d::Label* label = newLabel("Nothing Here Yet :)", 6);
                label->setPosition(centerWidth(), 880);

                _settings = Sprite::create("Rectangle.png");
                _settings->setPosition(520, 920);
                _settings->setScale(0.5);
                _settings->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
                this->addChild(_settings, 5);
            }
        }
    );
}

void MainMenuScene::BackButton(int x, int y, float scale, int layer) {
    Button* backButton = newButton("", "Button/Back.png", layer);
    backButton->setPosition(cocos2d::Vec2(x, y));
    backButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    backButton->setScale(scale);

    backButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
            }
        }
    );
}

void MainMenuScene::OpenInventory() {
    Button* inventoryButton = newButton("", "Button/InventoryIcon.png", 4);
    inventoryButton->setPosition(cocos2d::Vec2(535, 830));
    inventoryButton->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    inventoryButton->setScale(0.08);

    inventoryButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED && openSubMenus == false) {
                openSubMenus = true;

                BackButton(20, 210, 0.05, 5);

                _inventory = Sprite::create("Inventory.png");
                _inventory->setPosition(520, 950);
                _inventory->setScale(0.5);
                _inventory->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
                this->addChild(_inventory, 3);
            }
        }
    );
}

void MainMenuScene::TutoTextBox(int x, int y) {
    _textBox = Sprite::create("Button/Rectangle.png");
    _textBox->setPosition(x, y);
    _textBox->setScale(0.5);
    _textBox->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

    this->addChild(_textBox, 4);
}

void MainMenuScene::TutoNextButton() {
    Button* nextButton = newButton("", "Button/Back.png", 5);
    nextButton->setPosition(cocos2d::Vec2(120, 310));
    nextButton->setAnchorPoint(Vec2::ZERO);
    nextButton->setScale(0.05);

    nextButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
                _gameManager->setTutoPhases(1);
                if (_gameManager->getTutoPhases() == 10) {
                    _gameManager->setTutoCompleted(true); 
                }
            }
        }
    );
}

void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
