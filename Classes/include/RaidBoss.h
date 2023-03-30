#pragma once
#include "Entity.h"
#include "Enemy.h"
#include "Skill.h"
#include "GameManager.h"
#include <vector>
class RaidBoss : public Enemy
{

protected:
	std::string _name;
	int commonRate;
	int RareRate;
	int EpicRate;
	int LegendaryRate;
	int rarities[4];
	std::vector<int> dropType;

	GameManager *gameManager;
	void SetRarities(int);
	/*int[, ] GetRarities();*/
	 
	std::vector<int> getDrops();
	void SetDrop(int);

public:
	
	RaidBoss();
};

