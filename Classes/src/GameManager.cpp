#include "GameManager.h"

GameManager::GameManager()
{
	BossId = 0;
	BossLvl = 0;
	Difficulty = 0;
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

int GameManager::getDifficulty()
{
	return Difficulty;
}

void GameManager::setBossId(int id)
{
	BossId = id;
}

void GameManager::setBossLvl(int lvl)
{
	BossLvl = lvl;
}

void GameManager::setDifficulty(int difficulty)
{
	Difficulty = difficulty;
}

bool GameManager::isLoading() { return _loading; }
void GameManager::loading(bool loading) { _loading = loading; }