#include "MainMenuScene.h"
#include "BattleScene.h"
#include "RaidMenuScene.h"
#include "SummonMenuScene.h"
#include "CharacterMenu.h"
#include "ShopMenu.h"
#include "AudioEngine.h"

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

bool MainMenuScene::init()
{

    if (!Scene::init()) { return false; }
	_database = Database::Instance();

    openSubMenus = false;

    setScene(this);

    Sprites();
    Labels();
    Buttons();
    Sounds();

	
	if ((bool)!_database->user()->tutorial) { Tuto(); }

    return true;
}

void MainMenuScene::Tuto() {
    _gameManager->setTextPhases(1);
    newTutoNextButton();
    if (_gameManager->getTextPhases() == 1) {
       newTextBox("Hello and welcome to our headquarters! I'll help you make yourself at home."); // need to figure out a way to return to next line
    }
    else if (_gameManager->getTextPhases() == 2) {
        newTextBox("At the bottom you will find the raid menu! It is filled with hardships but is very rewarding");
    }
    else if (_gameManager->getTextPhases() == 3) {
        newTextBox("You will also find the shop and summoning book. In order to complete tough tasks you'll need help!");
    }
    else if (_gameManager->getTextPhases() == 4) {
        newTextBox("At the top right you will find a dropdown menu with the settings and your inventory.");
    }
    else if (_gameManager->getTextPhases() == 5) {
        newTextBox("Finally, at the top left you will find your beautiful self, anyways I better get going good luck adventurer!");
    }
    if (_gameManager->getTextPhases() == 5) {
		_database->user()->tutorial = 1;
		_database->updateUser();
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

	_energy = "Energy: " + std::to_string(_database->user()->energy);

	cocos2d::Label* energyy = newLabel(_energy, 1);
	energyy->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	energyy->setScale(0.7);
	energyy->setPosition(110, 920);

	//Sprite* _cristal = Sprite::create("Items / Cristal.png");
	//_cristal->setPosition(220, 910);
	//_cristal->setScale(0.05);
	//_cristal->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

	_crystal = "Crystal: " + std::to_string(_database->user()->cristals);

	cocos2d::Label* crystal = newLabel(_crystal, 2);
	crystal->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	crystal->setScale(0.7);
	crystal->setPosition(centerWidth(), 920);

	
	
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
			if (type == Widget::TouchEventType::ENDED && openSubMenus == false && (bool)_database->user()->tutorial) {
				cocos2d::Director::getInstance()->replaceScene(SummonMenuScene::create());
				AudioEngine::pause(audioID);
			}
		}
	);

	// STUFF 
	Button* characterButton = newButton("", "Button/characterbtn.png");
	characterButton->setPosition(cocos2d::Vec2(10, 935));
	characterButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	characterButton->setScale(0.7);

	characterButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED && (bool)_database->user()->tutorial) {
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
			if (type == Widget::TouchEventType::ENDED && openSubMenus == false && (bool)_database->user()->tutorial) {

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

				BackButton(190, 840, 0.03, 5);

				username = "Username: " + _database->user()->name;

				cocos2d::Label* user = newLabel(username, 5);
				user->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
				user->setScale(0.8);
				user->setPosition(215, 800);

				Button* editButton = newButton("", "Button/editbtn.png", 5);
				editButton->setPosition(cocos2d::Vec2(500, 805));
				editButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
				editButton->setScale(0.12);
				editButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
					{
						if (type == Widget::TouchEventType::ENDED) {
							TextField* name = TextField::create("Enter new pseudo", "fonts/Marker Felt.ttf", 30);
							name->setPosition(cocos2d::Vec2(315, 750));

							Button * okbtn = newButton("ok", "",5);
							okbtn->setPosition(cocos2d::Vec2(315, 720));

							okbtn->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
								{
									if (type == Widget::TouchEventType::BEGAN) {
										log("began");
									}
								}
							);
							this->addChild(name,5);
						}
					}
				);

				_background4 = Sprite::create("Button/Rectangle.png");
				_background4->setPosition(180, 850);
				_background4->setScale(0.5,0.25);
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

void MainMenuScene::newTutoNextButton() {
	Button* nextButton = newButton("", "Button/Back.png", 11);
	nextButton->setPosition(cocos2d::Vec2(110, 330));
	nextButton->setAnchorPoint(Vec2::ZERO);
	nextButton->setScale(0.05);

	nextButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED) {
				cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
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

				SoundsRect(x, 807);

				Button* increaseButton = newButton("", "Button/plusbtn.png", 6);
				increaseButton->setPosition(cocos2d::Vec2(440, 807));
				increaseButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
				increaseButton->setScale(0.08);
				increaseButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
					{
						if (type == Widget::TouchEventType::ENDED && musicVol <= 1.0f) {
							cocos2d::AudioEngine::setVolume(audioID, musicVol += 0.10f);

							SoundsRect(x += 40, 807);
						}
					}
				);

				Button* decreaseButton = newButton("", "Button/moinsbtn.png", 6);
				decreaseButton->setPosition(cocos2d::Vec2(20, 800));
				decreaseButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
				decreaseButton->setScale(0.25);
				decreaseButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
					{
						if (type == Widget::TouchEventType::ENDED) {
							cocos2d::AudioEngine::setVolume(audioID, musicVol -= 0.10f);
							//this->removeChild(sound, true);
							//this->removeChildByName("1"-1);
						}
					}
				);

				BackButton(460, 910, 0.05, 6);

				cocos2d::Label* label = newLabel("", 6);
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
	musicVol = 0.0f;
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