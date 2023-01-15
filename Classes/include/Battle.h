#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
#include "Enemy.h"

class Battle
{
protected:
	Player* _player;
	std::vector<Enemy*> _enemies;
	std::vector<Entity*> _battleOrder;
	bool _battle, _win;

public:
	Battle(Player*, std::vector<Enemy*>);
	~Battle();

	void attack(Entity*, Entity*);
	void turn();
	void battleCheck();
	bool getBattleState();

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

