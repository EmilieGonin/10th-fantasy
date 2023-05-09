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

	Playerr = newSprite("Sprite/player.png");
	Playerr->setPosition(200, 600);

	player = new Player(Database::Instance()->user());

	Playerr->setScale(2.5);
	EventListenerMouse* listener = EventListenerMouse::create();
	listener->onMouseUp = CC_CALLBACK_1(CharacterMenu::MouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->addChild(bg);
	this->addChild(Playerr, 1);
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
	if (equipBounds.containsPoint(_mousePosition))
	{
		player->equip(stuffToEquip);
		cocos2d::Director::getInstance()->replaceScene(CharacterMenu::create());
	}
	if (desequipBounds.containsPoint(_mousePosition))
	{
		player->unequip(stuffToEquip);
		cocos2d::Director::getInstance()->replaceScene(CharacterMenu::create());
	}
	std::vector<Rect> enemiesBounds;
}
void CharacterMenu::Stuff()
{
	Title = newLabel("STUFF");
	Title->setPosition(centerWidth(), 900);
	this->addChild(Title, 1);

	if (player->getCharacter()->gears[1] == 0)
	{
		Helmet = newButton("", "Stuff/Empty.png");
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
	}
	else {
		Helmet = newButton("", "Stuff/" + std::to_string(Database::Instance()->gears()[0][player->getCharacter()->gears[1] - 1].rarity) + "/" + std::to_string(Database::Instance()->gears()[0][player->getCharacter()->gears[1] - 1].type) + ".png");
		Helmet->setPosition(cocos2d::Vec2(100, 650));
		Helmet->setScale(0.15, 0.15);
		this->addChild(Helmet, 1);
		Helmet->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED) {
					BackButton();
					PopupGear(Database::Instance()->gears()[0][player->getCharacter()->gears[1] - 1]);
				}
			}
		);
	}
	if (player->getCharacter()->gears[2] == 0)
	{
		Chest = newButton("", "Stuff/Empty.png");
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
	}
	else {
		Chest = newButton("", "Stuff/" + std::to_string(Database::Instance()->gears()[0][player->getCharacter()->gears[2] - 1].rarity) + "/" + std::to_string(Database::Instance()->gears()[0][player->getCharacter()->gears[2] - 1].type) + ".png");
		Chest->setPosition(cocos2d::Vec2(100, 550));
		Chest->setScale(0.15, 0.15);
		this->addChild(Chest, 1);
		Chest->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED) {
					BackButton();
					PopupGear(Database::Instance()->gears()[0][player->getCharacter()->gears[2] - 1]);
				}
			}
		);
	}

	if (player->getCharacter()->gears[3] == 0)
	{
		Boots = newButton("", "Stuff/Empty.png");
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
	}
	else {
		Boots = newButton("", "Stuff/" + std::to_string(Database::Instance()->gears()[0][player->getCharacter()->gears[3] - 1].rarity) + "/" + std::to_string(Database::Instance()->gears()[0][player->getCharacter()->gears[3] - 1].type) + ".png");
		Boots->setPosition(cocos2d::Vec2(100, 400));
		Boots->setScale(0.15, 0.15);
		this->addChild(Boots, 1);
		Boots->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED) {
					BackButton();
					PopupGear(Database::Instance()->gears()[0][player->getCharacter()->gears[3] - 1]);
				}
			}
		);
	}


	Weapon = newButton("", "Stuff/Empty.png");
	Weapon->setPosition(cocos2d::Vec2(100, 300));
	Weapon->setScale(0.2, 0.2);
	this->addChild(Weapon, 1);


	if (player->getCharacter()->gears[5] == 0)
	{
		Earring = newButton("", "Stuff/Empty.png");
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
	}
	else {
		Earring = newButton("", "Stuff/" + std::to_string(Database::Instance()->gears()[0][player->getCharacter()->gears[5] - 1].rarity) + "/" + std::to_string(Database::Instance()->gears()[0][player->getCharacter()->gears[5] - 1].type) + ".png");

		Earring->setPosition(cocos2d::Vec2(450, 650));
		Earring->setScale(0.15, 0.15);
		this->addChild(Earring, 1);
		Earring->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED) {
					BackButton();
					PopupGear(Database::Instance()->gears()[0][player->getCharacter()->gears[5] - 1]);
				}
			}
		);
	}

	if (player->getCharacter()->gears[4] == 0)
	{
		Necklace = newButton("", "Stuff/Empty.png");
		Necklace->setPosition(cocos2d::Vec2(450, 550));
		Necklace->setScale(0.15, 0.15);
		this->addChild(Necklace, 1);
		Necklace->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED) {
					BackButton();
					PopupEmpty(4);
				}
			}
		);
	}
	else
	{
		Necklace = newButton("", "Stuff/" + std::to_string(Database::Instance()->gears()[0][player->getCharacter()->gears[4] - 1].rarity) + "/" + std::to_string(Database::Instance()->gears()[0][player->getCharacter()->gears[4] - 1].type) + ".png");
		Necklace->setPosition(cocos2d::Vec2(450, 550));
		Necklace->setScale(0.15, 0.15);
		this->addChild(Necklace, 1);
		Necklace->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED) {
					BackButton();
					PopupGear(Database::Instance()->gears()[0][player->getCharacter()->gears[4] - 1]);
				}
			}
		);
	}


	if (player->getCharacter()->gears[6] == 0)
	{
		Ring = newButton("", "Stuff/Empty.png");
		Ring->setPosition(cocos2d::Vec2(450, 400));
		Ring->setScale(0.15, 0.15);
		this->addChild(Ring, 1);
		Ring->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED) {
					BackButton();
					PopupEmpty(6);
				}
			}
		);
	}
	else
	{
		Ring = newButton("", "Stuff/" + std::to_string(Database::Instance()->gears()[0][player->getCharacter()->gears[6] - 1].rarity) + "/" + std::to_string(Database::Instance()->gears()[0][player->getCharacter()->gears[6] - 1].type) + ".png");
		Ring->setPosition(cocos2d::Vec2(450, 400));
		Ring->setScale(0.15, 0.15);
		this->addChild(Ring, 1);
		Ring->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED) {
					BackButton();
					PopupGear(Database::Instance()->gears()[0][player->getCharacter()->gears[6] - 1]);
				}
			}
		);
	}

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

	LvlUp = newLabel("Level : " + std::to_string(Database::Instance()->user()->level));
	LvlUp->setPosition(130, 180);
	LvlUp->setScale(0.8);
	this->addChild(LvlUp, 2);

	Label* hp = newLabel("Hp : " + std::to_string(*player->getTotalStats()[5]));
	hp->setPosition(130, 160);
	hp->setScale(0.8);
	this->addChild(hp, 2);

	Label* atk = newLabel("Attack : " + std::to_string(*player->getTotalStats()[0]));
	atk->setPosition(130, 140);
	atk->setScale(0.8);
	this->addChild(atk, 2);

	Label* matk = newLabel("Magical bonus : " + std::to_string(*player->getTotalStats()[1]) + "%");
	matk->setPosition(160, 120);
	matk->setScale(0.8);
	this->addChild(matk, 2);

	Label* patk = newLabel("Physical bonus : " + std::to_string(*player->getTotalStats()[2]) + "%");
	patk->setPosition(160, 100);
	patk->setScale(0.8);
	this->addChild(patk, 2);

	Label* mdef = newLabel("Magical Def : " + std::to_string(*player->getTotalStats()[3]));
	mdef->setPosition(350, 160);
	mdef->setScale(0.8);
	this->addChild(mdef, 2);

	Label* pdef = newLabel("Physical Def : " + std::to_string(*player->getTotalStats()[4]));
	pdef->setPosition(350, 140);
	pdef->setScale(0.8);
	this->addChild(pdef, 2);

	Label* critR = newLabel("Critical rate : " + std::to_string(*player->getTotalStats()[6]) + "%");
	critR->setPosition(350, 120);
	critR->setScale(0.8);
	this->addChild(critR, 2);

	Label* critD = newLabel("Critical Damage : " + std::to_string(*player->getTotalStats()[7]) + "%");
	critD->setPosition(360, 100);
	critD->setScale(0.8);
	this->addChild(critD, 2);


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
	for (int i = 0; i < _database->gears()->size(); i++)
	{
		log(i);


		if (_database->gears()[0][i].type == gearType)
		{

			Sprite* item = newSprite("Stuff/" + std::to_string(_database->gears()[0][i].rarity) + "/" + std::to_string(_database->gears()[0][i].type) + ".png");
			item->setPosition(cocos2d::Vec2(10 + count * 110, 800 - 60 * count % 5));
			item->setScale(0.2, 0.2);
			item->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);;
			Rect boundingBox = item->getBoundingBox();
			displayedSprite.push_back(item);
			boundings.push_back(boundingBox);
			allGears.push_back(_database->gears()[0][i]);
			this->addChild(item, 2);
			count++;
		}
	}

}

void CharacterMenu::PopupGear(db::gear myGear)
{
	stuffToEquip = myGear;
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


	equipp = newSprite("Button/plusbtn.png");
	equipp->setPosition(cocos2d::Vec2(185, 440));
	equipp->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	equipp->setScale(0.05);
	equipBounds = equipp->getBoundingBox();

	unequip = newSprite("Button/moinsbtn.png");
	unequip->setPosition(cocos2d::Vec2(140, 440));
	unequip->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	unequip->setScale(0.25);
	desequipBounds = unequip->getBoundingBox();







	this->addChild(equipp, 2);
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
		this->removeChild(equipp);
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

