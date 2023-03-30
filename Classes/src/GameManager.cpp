#include "GameManager.h"

GameManager::GameManager()
{
	BossId = 0;
	BossLvl = 0;
	bossSprites[0] = "Sprite/DifficultyBetala.png";
	bossSprites[1] = "Sprite/DifficultyShado.png";
	bossSprites[2] = "Sprite/DifficultyLaijande.png";
}

GameManager* GameManager::_instance = new GameManager();

GameManager* GameManager::Instance() {
	return _instance;
}


int GameManager::getBossId()
{
	return BossId;
}

int GameManager::getBossLvl()
{
	return BossLvl;
}

std::string GameManager::getSprite()
{
	return bossSprites[BossId-1];
}

void GameManager::setBossId(int id)
{
	BossId = id;
}

void GameManager::setBossLvl(int lvl)
{
	BossLvl = lvl;
}

