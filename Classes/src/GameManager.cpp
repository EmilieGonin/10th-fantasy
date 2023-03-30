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

bool GameManager::getTutoCompleted() {
	return TutoCompleted;
}

int GameManager::getTutoPhases() {
	return TutoPhases;
}

void GameManager::setBossId(int id)
{
	BossId = id;
}

void GameManager::setBossLvl(int lvl)
{
	BossLvl = lvl;
}

void GameManager::setTutoCompleted(bool tuto) {
	TutoCompleted = tuto;
}

void GameManager::setTutoPhases(int phase) {
	TutoPhases += phase;
}

bool GameManager::isLoading() { return _loading; }
void GameManager::loading(bool loading) { _loading = loading; }
