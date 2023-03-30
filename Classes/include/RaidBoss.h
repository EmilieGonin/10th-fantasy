#pragma once
#include "Entity.h"
#include "Enemy.h"
#include "Skill.h"
#include <vector>
class RaidBoss : public Enemy
{

protected:
	std::string _name;
	int _rarities[4];
	std::vector<int> _dropType;
	void setDrop(int);
	std::vector<int> getDrops();

	enum RarityName {
		common = 0,
		rare = 1,
		epic = 2,
		legendary = 3
	};
public:
	
	void setRarities(int);
	int* getRarities();
	RaidBoss();
};

