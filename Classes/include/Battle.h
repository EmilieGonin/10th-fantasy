#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
#include "Entity.h"
#include "Enemy.h"
#include "Skill.h"
#include "Interface.h"
#include "GameManager.h"
#include "Database.h"
#include <random>

class Battle : public Interface
{
protected:
	GameManager* gameManager;
	Database* database;
	Player* _player;
	std::vector<Enemy*> _enemies;
	cocos2d::DrawNode *myLifeBar;
	cocos2d::Label* myDamage;
	cocos2d::Vec2 rectangle[4];
	cocos2d::DrawNode* enemyLifeBar;
	cocos2d::Vec2 rectangle2[4];
	std::vector<Entity*> _battleOrder;
	bool _battle, _win;
	bool _myTurn;
	int selectedSkill, iPlay, selectedEnemy;

public:
	Battle(Player*, std::vector<Enemy*>, int); // 0 normal battle, 1 raid battle
	~Battle();

	void attack(Entity*, Entity*, Skill*);
	void play();
	void battleCheck();
	bool getBattleState();
	int getSelected();
	void setSelected(int);
	void selectEnemy(int);
	bool getMyTurn();
	void drop();
	db::gear createNecklace(int*);
	db::gear createEarRing(int*);
	db::gear createRing(int*);
	db::gear createHelmet(int*);
	db::gear createChest(int*);
	db::gear createBoots(int*);

	cocos2d::DrawNode* getLifeBar();
	cocos2d::DrawNode* getEnemyLifeBar();
	void updateLifeBar();

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
};

