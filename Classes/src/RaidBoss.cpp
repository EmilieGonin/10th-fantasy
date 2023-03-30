#include "RaidBoss.h"


RaidBoss::RaidBoss()
{
	for (int i = 0; i < 4; i++) {
		_rarities[i] = 0;
	}
}

void RaidBoss::setRarities(int difficulty) {

	switch (difficulty)
	{
	case 1:
		_rarities[common] = 100;
		break;
	case 2:
		_rarities[common] = 70;
		_rarities[rare] = 30;
		break;
	case 3:
		_rarities[common] = 30;
		_rarities[rare] = 50;
		_rarities[epic] = 20;
		break;
	case 4:
		_rarities[rare] = 70;
		_rarities[epic] = 30;
		break;
	case 5:
		_rarities[rare] = 30;
		_rarities[epic] = 60;
		_rarities[legendary] = 10;
		break;
	case 6:
		_rarities[epic] = 80;
		_rarities[legendary] = 20;
	}
}
void RaidBoss::setDrop(int bossType)
{
	switch (bossType)
	{
	case 1: 
		_dropType.push_back(0);
		break;
	case 2:
		_dropType.push_back(4);
		_dropType.push_back(5);
		_dropType.push_back(6);
		break;
	case 3: 
		_dropType.push_back(1);
		_dropType.push_back(2);
		_dropType.push_back(3);
		break;
	}
}

std::vector<int> RaidBoss::getDrops()
{
	return _dropType;
}


int* RaidBoss::getRarities() {
	return _rarities;
}
	

