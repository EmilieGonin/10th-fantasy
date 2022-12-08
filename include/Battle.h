#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
#include "Entity.h"
#include "Enemy.h"

class Battle
{

	Player* player;
	std::vector<Enemy*> enemies;
	std::vector<Entity*> battleOrder;

	bool battle, win;
public:
	Battle(Player*, std::vector<Enemy*>);
	~Battle();

	void attack(Entity*, Entity*);
	void turn();
	void battleCheck();
	bool getBattleState();

};

