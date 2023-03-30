#include "BattleScene.h"
#include "cocos2d.h"
#include "Entity.h"
#include "Player.h"
#include "Gear.h"
#include "Weapon.h"
#include "Sword.h"
#include "Battle.h"
#include "RaidBossBetala.h"
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

// on "init" you need to initialize your instance
bool BattleScene::init()
{
	//////////////////////////////
	// 1. super init first


	if (!Scene::init())
	{
		return false;
	}

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

	gameManager = GameManager::Instance();
	RaidBossBetala* boss;
	switch (gameManager->getBossId()){
	case 0://UwU
		break;
	case 1: 
		boss = new RaidBossBetala(gameManager->getBossLvl());
		_enemies.push_back(boss);
		break;
	case 2:
		boss = new RaidBossBetala(gameManager->getBossLvl());
		_enemies.push_back(boss);
		break;
	case 3:
		boss = new RaidBossBetala(gameManager->getBossLvl());
		_enemies.push_back(boss);
		break;
		
	}
	
	db::gear Helmet;
	Helmet.type = HELMET;
	Helmet.stat = HP;
	Helmet.amount = 3000;
	Helmet.rarity = LEGENDARY;
	Helmet.level = 0;

	db::gear Chest;
	Chest.type = CHEST;
	Chest.stat = PDEF;
	Chest.amount = 25;
	Chest.rarity = LEGENDARY;
	Chest.level = 0;

	db::gear Boots;
	Boots.type = BOOT;
	Boots.stat = HP;
	Boots.amount = 200;
	Boots.rarity = LEGENDARY;
	Boots.level = 0;

	db::gear Rings;
	Boots.type = RING;
	Boots.stat = PATK;
	Boots.amount = 250;
	Boots.rarity = LEGENDARY;
	Boots.level = 0;

	db::gear Necklace;
	Necklace.type = NECKLACE;
	Necklace.stat = PATK;
	Necklace.amount = 250;
	Necklace.rarity = LEGENDARY;
	Necklace.level = 0;

	db::gear Earrings;
	Earrings.type = EARRING;
	Earrings.stat = CD;
	Earrings.amount = 15;
	Earrings.rarity = LEGENDARY;
	Earrings.level = 0;
	
	std::vector<db::stat> effect;
	db::stat EffectTheaume;
	EffectTheaume.percentage = 1;
	EffectTheaume.statId = ATK;
	EffectTheaume.rate = 50;
	effect.push_back(EffectTheaume);

	db::support Theaume;
	Theaume.name = "Theaume";
	Theaume.rarity = LEGENDARY;
	Theaume.type = 2;
	Theaume.stats = effect;
	
	
	Support theaume(&Theaume);
	/*enemies.push_back(boss);*/
	Gear helmet(&Helmet);
	Gear chest(&Chest);	
	Gear legs(&Boots);
	Gear rings(&Rings);
	Gear necklace(&Necklace);
	Gear earrings(&Earrings);

	player = new Player();
	Sword* sword = new Sword(50);

	player->equipSupport(&theaume);
	player->equipSupport(&theaume);
	player->equip(&helmet);	
	player->equip(&chest);
	//player->equip(&rings);
	player->equip(&necklace);
	player->equipWeapon(sword);


	Battle* raidBattle =  new Battle(player, _enemies, 1);
	battle = raidBattle;

	cocos2d::Sprite* background = Sprite::create("BattleScene.png");
	background->setPosition(0, 0);
	background->setScale(0.5);
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
		_enemies[i]->getSprite()->setPosition(150 + i * 50, 250);
		_enemies[i]->getSprite()->setScale(0.5);
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


