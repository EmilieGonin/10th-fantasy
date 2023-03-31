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

bool CharacterMenu::init()
{
	if (!Scene::init()) { return false; }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	bg = newSprite("Background/characterbg.png");
	bg->setPosition(centerWidth(), centerHeight());
	bg->setScale(3);

	Player = newSprite("Sprite/player.png");
	Player->setPosition(200, 600);

	Player->setScale(2.5);
	EventListenerMouse* listener = EventListenerMouse::create();
	listener->onMouseUp = CC_CALLBACK_1(CharacterMenu::MouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->addChild(bg);
	this->addChild(Player, 1);
	Supports();
	Stuff();
	Stat();
	return true;
}

void CharacterMenu::MouseUp(Event* event) {
	EventMouse* e = (EventMouse*)event;
	int button = e->getCursorX();
	cocos2d::log("%d", button);
	_mousePosition = e->getLocationInView();
	for (int i = 0; i < boundings.size(); i++)
	{
		if (boundings[i].containsPoint(_mousePosition))
		{
			PopupGear(allGears[i]);
		}
	}
	std::vector<Rect> enemiesBounds;
}
void CharacterMenu::Stuff()
{
	Title = newLabel("STUFF");
	Title->setPosition(centerWidth(), 900);
	this->addChild(Title, 1);


	Helmet = newButton("", "Stuff/helmet.png");
	Helmet->setPosition(cocos2d::Vec2(100, 650));
	Helmet->setScale(0.15, 0.15);
	this->addChild(Helmet, 1);
	Helmet->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED) {
				BackButton();
				PopupEmpty(1);
			}
		}
	);

	Chest = newButton("", "Stuff/chest.png");
	Chest->setPosition(cocos2d::Vec2(100, 550));
	Chest->setScale(0.15, 0.15);
	this->addChild(Chest, 1);
	Chest->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED) {
				BackButton();
				PopupEmpty(2);
			}
		}
	);

	Boots = newButton("", "Stuff/boots.png");
	Boots->setPosition(cocos2d::Vec2(100, 400));
	Boots->setScale(0.15, 0.15);
	this->addChild(Boots, 1);
	Boots->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED) {
				BackButton();
				PopupEmpty(3);
			}
		}
	);

	Weapon = newButton("", "Stuff/chest.png");
	Weapon->setPosition(cocos2d::Vec2(100, 300));
	Weapon->setScale(0.2, 0.2);
	this->addChild(Weapon, 1);

	Earring = newButton("", "Stuff/earring.png");
	Earring->setPosition(cocos2d::Vec2(450, 650));
	Earring->setScale(0.15, 0.15);
	this->addChild(Earring, 1);
	Earring->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED) {
				BackButton();
				PopupEmpty(5);
			}
		}
	);

	Necklace = newButton("", "Stuff/necklace.png");
	Necklace->setPosition(cocos2d::Vec2(450, 550));
	Necklace->setScale(0.15, 0.15);
	this->addChild(Necklace, 1);
	Necklace->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED) {
				BackButton();
				PopupEmpty(6);
			}
		}
	);

	Ring = newButton("", "Stuff/ring.png");
	Ring->setPosition(cocos2d::Vec2(450, 400));
	Ring->setScale(0.15, 0.15);
	this->addChild(Ring, 1);
	Ring->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED) {
				BackButton();
				PopupEmpty(4);
			}
		}
	);

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

	bg = newSprite("Rectangle.png");
	bg->setPosition(cocos2d::Vec2(centerWidth(), 150));
	bg->setScale(0.4, 0.3);
	this->addChild(bg, 1);

}

void CharacterMenu::Supports()
{
	FirstSup = newButton("", "Supports/djeamy.png");
	FirstSup->setPosition(cocos2d::Vec2(100, 780));
	FirstSup->setScale(0.1, 0.1);
	this->addChild(FirstSup, 1);


	SecondSup = newButton("", "Supports/elf.png");
	SecondSup->setPosition(cocos2d::Vec2(450, 780));
	SecondSup->setScale(0.1, 0.1);
	this->addChild(SecondSup, 1);

}

void CharacterMenu::PopupEmpty(int gearType)
{
	popup = newSprite("Rectangle.png");
	popup->setPosition(10, 850);
	popup->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	popup->setScale(0.5, 0.8);
	displayedSprite.push_back(popup);
	this->addChild(popup, 1);
	int count = 0;
	for (int i = 0; i < _database->inventory()->gears.size(); i++)
	{
		log(i);
		if (_database->inventory()->gears[i].type == gearType)
		{

			Sprite* item = newSprite("Stuff/" + std::to_string(_database->inventory()->gears[i].rarity) + "/" + std::to_string(_database->inventory()->gears[i].type) + ".png");
			item->setPosition(cocos2d::Vec2(10 + count * 110, 800 - 60 * count % 5));
			item->setScale(0.2, 0.2);
			item->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);;
			Rect boundingBox = item->getBoundingBox();
			displayedSprite.push_back(item);
			boundings.push_back(boundingBox);
			allGears.push_back(_database->inventory()->gears[i]);
			this->addChild(item, 2);
			count++;
		}
	}

}

void CharacterMenu::PopupGear(db::gear myGear)
{

	for (int i = 0; i < displayedSprite.size(); i++)
	{
		this->removeChild(displayedSprite[i]);
	}
	popup = newSprite("Rectangle.png");
	popup->setPosition(10, 850);
	popup->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	popup->setScale(0.5, 0.8);
	this->addChild(popup, 1);

	perso = newSprite("Stuff/" + std::to_string(myGear.rarity) + "/" + std::to_string(myGear.type) + ".png");
	perso->setPosition(20, 780);
	perso->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	perso->setScale(0.1, 0.1);
	this->addChild(perso, 2);

	stats = newLabel(std::to_string(myGear.type) + "  :  " + std::to_string(myGear.amount));
	stats->setPosition(centerWidth(), 750);
	this->addChild(stats, 2);

	rarity = newLabel("Rarity : " + std::to_string(myGear.rarity));
	rarity->setPosition(185, 700);
	this->addChild(rarity, 2);

	upgrade = newButton("", "Button/Back.png");
	upgrade->setPosition(cocos2d::Vec2(250, 440));
	upgrade->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	upgrade->setScale(0.05);
	this->addChild(upgrade, 2);

	equip = newButton("", "Button/plusbtn.png");
	equip->setPosition(cocos2d::Vec2(185, 440));
	equip->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	equip->setScale(0.05);
	this->addChild(equip, 2);

	unequip = newButton("", "Button/moinsbtn.png");
	unequip->setPosition(cocos2d::Vec2(330, 430));
	unequip->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	unequip->setScale(0.1);
	this->addChild(unequip, 2);
}


void CharacterMenu::BackButton() {


	backButton = newButton("", "Button/Back.png");
	backButton->setPosition(cocos2d::Vec2(20, 840));
	backButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	backButton->setScale(0.05);
	this->addChild(backButton, 2);
	backButton->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
		{
			for (int i = 0; i < displayedSprite.size(); i++)
			{
				this->removeChild(displayedSprite[i]);
			}
			if (type == Widget::TouchEventType::ENDED) {
				this->removeChild(popup);
				this->removeChild(backButton);
				this->removeChild(unequip);
				this->removeChild(equip);
				this->removeChild(upgrade);
				this->removeChild(rarity);
				this->removeChild(stats);
				this->removeChild(perso);
			}
				displayedSprite.clear();
				boundings.clear();
				allGears.clear();
		}
	);
}


void CharacterMenu::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}

