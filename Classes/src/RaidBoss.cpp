#include "RaidBoss.h"


RaidBoss::RaidBoss()
{
	gameManager = GameManager::Instance();
	commonRate = 0;
	RareRate = 0;
	EpicRate = 0;
	LegendaryRate = 0;
	SetRarities(gameManager->getDifficulty());
}

void RaidBoss::SetRarities(int difficulty) {

	switch (difficulty)
	{
	case 1:
		commonRate = 100;
		break;
	case 2:
		commonRate = 70;
		RareRate = 30;
		break;
	case 3:
		commonRate = 30;
		RareRate = 50;
		EpicRate = 20;
		break;
	case 4:
		RareRate = 70;
		EpicRate = 30;
		break;
	case 5:
		RareRate = 30;
		EpicRate = 60;
		LegendaryRate = 10;
		break;
	case 6:
		EpicRate = 80;
		LegendaryRate = 20;
	}
}
void RaidBoss::SetDrop(int bossType)
{
	switch (bossType)
	{
	case 1: 
		dropType.push_back(0);
		break;
	case 2:
		dropType.push_back(4);
		dropType.push_back(5);
		dropType.push_back(6);
		break;
	case 3: 
		dropType.push_back(1);
		dropType.push_back(2);
		dropType.push_back(3);
		break;
	}
}

std::vector<int> RaidBoss::getDrops()
{
	return dropType;
}


//int[] RaidBoss::GetRarities() {
//	return rarities;
//}
	

