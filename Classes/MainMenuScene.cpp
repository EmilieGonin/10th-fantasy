#include "MainMenuScene.h"
#include "BattleScene.h"
#include "RaidMenuScene.h"
#include "SummonMenuScene.h"
#include "CharacterMenu.h"
#include "ShopMenu.h"
#include "AudioEngine.h"
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
    Sounds();

    return true;
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
    raidButton->setScale(0.2);

    raidButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED && openSubMenus == false) {
                cocos2d::Director::getInstance()->replaceScene(RaidMenuScene::create());  
                AudioEngine::pause(audioID);
            }
        }
    );
    // SHOP
    Button* shopButton = newButton("", "Button/Shop.png", 3);
    shopButton->setPosition(cocos2d::Vec2(225, 23));
    shopButton->setAnchorPoint(Vec2::ZERO);
    shopButton->setScale(0.25);

    shopButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED && openSubMenus == false) {
                cocos2d::Director::getInstance()->replaceScene(ShopMenu::create());  
                AudioEngine::pause(audioID);
            }
        }
    );
    // SUMMON
    Button* summonButton = newButton("", "Button/Summon.png", 3);
    summonButton->setPosition(cocos2d::Vec2(40, 23));
    summonButton->setAnchorPoint(Vec2::ZERO);
    summonButton->setScale(0.185);

    summonButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED && openSubMenus == false) {
                cocos2d::Director::getInstance()->replaceScene(SummonMenuScene::create());
                AudioEngine::pause(audioID);
            }
        }
    );

    // INVENTORY 
    Button* characterButton = newButton("", "Button/characterbtn.png");
    characterButton->setPosition(cocos2d::Vec2(10, 935));
    characterButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    characterButton->setScale(0.7);

    characterButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED) {
                cocos2d::Director::getInstance()->replaceScene(CharacterMenu::create());
                AudioEngine::pause(audioID);
            }
        }
    );

    // DROPDOWN
    Button* dropDownButton = newButton("", "Button/DropDown.png", 2);
    dropDownButton->setPosition(cocos2d::Vec2(535, 880));
    dropDownButton->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    dropDownButton->setScale(0.045);

    dropDownButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED && openSubMenus == false) {

                Account();
                OpenInventory();
                Settings();
                _dropDownMenu = Sprite::create("DropDownMenu.png");
                _dropDownMenu->setPosition(540, 900);
                _dropDownMenu->setScale(0.25);
                _dropDownMenu->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
                this->addChild(_dropDownMenu, 3);
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
                openSubMenus = false;
            }
        }
    );
}

void MainMenuScene::Account()
{
    Button* profileButton = newButton("", "Button/Profile.png", 4);
    profileButton->setPosition(cocos2d::Vec2(535, 865));
    profileButton->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    profileButton->setScale(0.04);

    profileButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED && openSubMenus == false) {

                openSubMenus = true;

                BackButton(200, 850, 0.03, 5);

                //username = "Username: " + _database->user()->name;

                //cocos2d::Label* user = newLabel(username, 5);
                //user->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
                //user->setScale(0.8);
                //user->setPosition(215, 800);

                Button* editButton = newButton("", "Button/editbtn.png", 5);
                editButton->setPosition(cocos2d::Vec2(300, 800));
                editButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
                editButton->setScale(0.15);
                editButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
                    {
                        if (type == Widget::TouchEventType::ENDED) {

                        }
                    }
                );

                _background4 = Sprite::create("Button/Rectangle.png");
                _background4->setPosition(200, 850);
                _background4->setScale(0.25);
                _background4->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
                this->addChild(_background4, 4);
            }
        }
    );
}

void MainMenuScene::OpenInventory() {
    Button* inventoryButton = newButton("", "Button/InventoryIcon.png", 4);
    inventoryButton->setPosition(cocos2d::Vec2(535, 819));
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

void MainMenuScene::Settings() {
    Button* settingsButton = newButton("", "Button/Settings.png", 4);
    settingsButton->setPosition(cocos2d::Vec2(535, 775));
    settingsButton->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    settingsButton->setScale(0.08);

    settingsButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
        {
            if (type == Widget::TouchEventType::ENDED && openSubMenus == false) {
                openSubMenus = true;

                SoundsRect(80, 807);

                Button* increaseButton = newButton("", "Button/plusbtn.png", 6);
                increaseButton->setPosition(cocos2d::Vec2(400, 807));
                increaseButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
                increaseButton->setScale(0.08);
                increaseButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
                    {
                        if (type == Widget::TouchEventType::ENDED) {
                            cocos2d::AudioEngine::setVolume(audioID, musicVol+=0.10f);

                            SoundsRect(x+=40, 807);
                        }
                    }
                );   

                Button* decreaseButton = newButton("", "Button/moinsbtn.png", 6);
                decreaseButton->setPosition(cocos2d::Vec2(40, 800));
                decreaseButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
                decreaseButton->setScale(0.25);
                decreaseButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
                    {
                        if (type == Widget::TouchEventType::ENDED) {
                            cocos2d::AudioEngine::setVolume(audioID, musicVol-=0.10f);
                            //SoundsRect(420, 807, 6);
                            this->removeChild(sound, true);
                            //this->removeChildByTag();

                        }
                    }
                );
                BackButton(460, 910, 0.05, 6);

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

void MainMenuScene::Sounds() {
    musicVol = 0.1f;
    audioID = AudioEngine::play2d("Audio/melody-of-nature-main.mp3", true, musicVol);
   
}

void MainMenuScene::SoundsRect(int x, int y)
{
    sound = newSprite("white_rect.png");
    sound->setPosition(cocos2d::Vec2(x, y));
    sound->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    sound->setScale(0.3);
    sound->setLocalZOrder(6);

}

void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
