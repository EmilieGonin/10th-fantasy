#include "BattleScene.h"
#include "cocos2d.h"
#include "Entity.h"
#include "Player.h"
#include "Gear.h"
#include "Weapon.h"
#include "Sword.h"
#include "Battle.h"
#include "RaidBossBetala.h"
#include "RaidBossShaDo.h"
#include "RaidBossLaiJande.h"
#include <vector>
USING_NS_CC;	

Scene* BattleScene::createScene()
{
	return BattleScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool BattleScene::init()
{
	if (!Scene::init()) { return false; }

	enum Stats {
		ATK = 0,
		MATK = 1,
		PATK = 2,
		MDEF = 3,
		PDEF = 4,
		HP = 5,
		CR = 6,
		CD = 7
	};

	enum Stuff {
		WEAPON = 0,
		HELMET = 1,
		CHEST = 2,
		BOOT = 3,
		RING = 4,
		EARRING = 5,
		NECKLACE = 6,
	};

	enum Rarity {
		COMMON = 0,
		RARE = 1,
		EPIC = 2,
		LEGENDARY = 3,
	};

	db::gear Helmet;
	Helmet.type = gameManager->HELMET;
	Helmet.stat = gameManager->HP;
	Helmet.amount = 3000;
	Helmet.rarity = gameManager->LEGENDARY;
	Helmet.level = 0;

	db::gear Chest;
	Chest.type = gameManager->CHEST;
	Chest.stat = gameManager->PDEF;
	Chest.amount = 25;
	Chest.rarity = gameManager->LEGENDARY;
	Chest.level = 0;

	db::gear Boots;
	Boots.type = gameManager->BOOT;
	Boots.stat = gameManager->HP;
	Boots.amount = 200;
	Boots.rarity = gameManager->LEGENDARY;
	Boots.level = 0;

	db::gear Rings;
	Rings.type = gameManager->RING;
	Rings.stat = gameManager->PATK;
	Rings.amount = 250;
	Rings.rarity = gameManager->LEGENDARY;
	Rings.level = 0;

	db::gear Necklace;
	Necklace.type = gameManager->NECKLACE;
	Necklace.stat = gameManager->PATK;
	Necklace.amount = 250;
	Necklace.rarity = gameManager->LEGENDARY;
	Necklace.level = 0;

	db::gear Earrings;
	Earrings.type = gameManager->EARRING;
	Earrings.stat = gameManager->CD;
	Earrings.amount = 15;
	Earrings.rarity = gameManager->LEGENDARY;
	Earrings.level = 0;

	std::vector<db::stat> effect;
	db::stat EffectTheaume;
	EffectTheaume.percentage = 1;
	EffectTheaume.statId = gameManager->ATK;
	EffectTheaume.rate = 50;
	effect.push_back(EffectTheaume);

	/*enemies.push_back(boss);*/
	Gear helmet(&Helmet);
	Gear chest(&Chest);
	Gear legs(&Boots);
	Gear rings(&Rings);
	Gear necklace(&Necklace);
	Gear earrings(&Earrings);

	player = new Player(_database->user());
	Sword* sword = new Sword(50);
	player->equipWeapon(sword);
	db::support support = _database->getSupport(10);
	player->equipSupport(new Support(&support));
	player->equipSupport(new Support(&support));

	gameManager = GameManager::Instance();
	cocos2d::Sprite* background = Sprite::create(gameManager->getBackground());
	
	switch (gameManager->getBossId()){
	case 0://UwU
		break;
	case 1: 
		gameManager->setBoss(new RaidBossBetala(gameManager->getBossLvl()));
		_enemies.push_back(gameManager->getBoss());
		break;
	case 2:
		gameManager->setBoss(new RaidBossShaDo(gameManager->getBossLvl()));
		_enemies.push_back(gameManager->getBoss());
		break;
	case 3:
		gameManager->setBoss(new RaidBossLaiJande(gameManager->getBossLvl()));
		_enemies.push_back(gameManager->getBoss());
		break;
		
	}
	
	
	

	Battle* raidBattle =  new Battle(player, _enemies, 1);
	battle = raidBattle;

	
	background->setPosition(-650, 100);
	background->setScale(1.2);
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

	EventListenerMouse* listener = EventListenerMouse::create();
	listener->onMouseUp = CC_CALLBACK_1(BattleScene::MouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->addChild(background);
	this->addChild(player->getSprite());
	this->addChild(battle->getLifeBar());
	this->addChild(battle->getEnemyLifeBar());

	for (int i = 0; i < _enemies.size(); i++)
	{
		//_enemies[i]->getSprite()->setPosition(400 + i * 50, 100);
		//_enemies[i]->getSprite()->setPosition(150 + i * 50, 250);
		_enemies[i]->getSprite()->setPosition(220, 250);

		_enemies[i]->getSprite()->setScale(0.8);
		_enemies[i]->getSprite()->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		this->addChild(_enemies[0]->getSprite());
	}

	for (int i = 0; i < player->getSkills().size(); i++)
	{
		CCLOG("okok");
		player->getSkills()[i]->getSprite()->setPosition(50 + i * 150, 100);
		player->getSkills()[i]->getSprite()->setScale(0.1);

		player->getSkills()[i]->getSprite()->setAnchorPoint(Vec2::ZERO);
		this->addChild(player->getSkills()[i]->getSprite());
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->schedule(CC_SCHEDULE_SELECTOR(BattleScene::loop), 1);

  return true;
}
void BattleScene::loop(float delta)
{
	if (battle->getMyTurn() == false)
	{

		for (int i = 0; i < player->getSkills().size(); i++)
		{
			player->getSkills()[i]->getSprite()->setVisible(false);
		}
	}
	else {
		for (int a = 0; a< player->getSkills().size(); a++)
		{	
			player->getSkills()[a]->getSprite()->setVisible(true);
			if (player->getSkills()[a]->_cooldown > 0)
			{
				player->getSkills()[a]->getSprite()->setColor(Color3B::RED);
			}
		}
	}


}
void BattleScene::MouseUp(Event * event) {
	EventMouse* e = (EventMouse*)event;
	int button = e->getCursorX();
	cocos2d::log("%d", button);
	_mousePosition = e->getLocationInView();
	Rect s1Bounds = player->getSkills()[0]->getSprite()->getBoundingBox();
	Rect s2Bounds = player->getSkills()[1]->getSprite()->getBoundingBox();
	std::vector<Rect> enemiesBounds;

		if (s1Bounds.containsPoint(_mousePosition)) {
			battle->setSelected(0);
			player->getSkills()[0]->getSprite()->setColor(Color3B::YELLOW);
			player->getSkills()[1]->getSprite()->setColor(Color3B::WHITE);
		}
		if (s2Bounds.containsPoint(_mousePosition)) {
			if (player->getSkills()[1]->getCooldown() == 0)
			{
				player->getSkills()[1]->getSprite()->setColor(Color3B::YELLOW);
				player->getSkills()[0]->getSprite()->setColor(Color3B::WHITE);
				battle->setSelected(1);
			}
			else {
				CCLOG("pas dispo");
			}
			
		}
	
if (battle->getSelected() >= 0)
{
		for (int i = 0; i < _enemies.size(); i++)
		{

			Rect bound = _enemies[i]->getSprite()->getBoundingBox();
			enemiesBounds.push_back(bound);
		}
		for (int i = 0; i < enemiesBounds.size(); i++)
		{
		
			if (enemiesBounds[i].containsPoint(_mousePosition)) {
				battle->selectEnemy(i);
				player->getSkills()[1]->getSprite()->setColor(Color3B::WHITE);
				player->getSkills()[0]->getSprite()->setColor(Color3B::WHITE);
			}
		}
	}
}