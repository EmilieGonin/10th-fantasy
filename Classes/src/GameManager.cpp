#include "GameManager.h"

GameManager::GameManager()
{
	BossId = 0;
	BossLvl = 0;
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

void GameManager::setBossId(int id)
{
	BossId = id;
}

void GameManager::setBossLvl(int lvl)
{
	BossLvl = lvl;
}