#include "GameManager.h"


GameManager* GameManager::_instance = new GameManager();

GameManager::GameManager()

{
	_boss = new RaidBoss();
	_bossId = 0;
	_bossLvl = 0;
	_difficulty = 0;
	_tutoCompleted = true;
	_tutoPhases = 0;
	_loading = false;
	bossSprites[0] = "Sprite/DifficultyBetala.png";
	bossSprites[1] = "Sprite/DifficultyShado.png";
	bossSprites[2] = "Sprite/DifficultyLaijande.png";
}

GameManager* GameManager::Instance() { return _instance; }

//Getters
int GameManager::getBossId() { return _bossId; }
int GameManager::getBossLvl() { return _bossLvl; }
int GameManager::getDifficulty() { return _difficulty; }
bool GameManager::getTutoCompleted() { return _tutoCompleted; }
int GameManager::getTutoPhases() { return _tutoPhases; }
std::string GameManager::getSprite()
{
	return bossSprites[_bossId-1];
}

bool GameManager::isLoading() { return _loading; }
RaidBoss* GameManager::getBoss() { return _boss; }

//Setters
void GameManager::setBossId(int id) { _bossId = id; }
void GameManager::setBossLvl(int lvl) { _bossLvl = lvl; }
void GameManager::setDifficulty(int difficulty) { _difficulty = difficulty; }
void GameManager::setTutoCompleted(bool tuto) { _tutoCompleted = tuto; }
void GameManager::setTutoPhases(int phase) { _tutoPhases += phase; }
void GameManager::loading(bool loading) { _loading = loading; }
void GameManager::setBoss(RaidBoss* boss){ _boss = boss; }

