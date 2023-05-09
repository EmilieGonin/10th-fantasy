#include "GameManager.h"

GameManager* GameManager::_instance = new GameManager();

GameManager::GameManager()
{
	_bossId = 0;
	_bossLvl = 0;
	_difficulty = 0;
	_phases = 0;
	_boss = nullptr;
	_loading = false;

	//Stock this in raidboss sub classes instead;
	bossSprites[0] = "Sprite/DifficultyBetala.png";
	bossSprites[1] = "Sprite/DifficultyShado.png";
	bossSprites[2] = "Sprite/DifficultyLaijande.png";

	backgroundSprites[0] = "Sprite/dark.png";
	backgroundSprites[1] = "Sprite/red.png";
	backgroundSprites[2] = "Sprite/white.png";
}

GameManager* GameManager::Instance() { return _instance; }

//Getters
int GameManager::getBossId() { return _bossId; }
int GameManager::getBossLvl() { return _bossLvl; }
int GameManager::getDifficulty() { return _difficulty; }
int GameManager::getTextPhases() { return _phases; }
std::string GameManager::getBackground() { return backgroundSprites[_bossId-1]; }

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
void GameManager::setTextPhases(int phase) { _phases += phase; }
void GameManager::loading(bool loading) { _loading = loading; }
void GameManager::setBoss(RaidBoss* boss){
	_boss = boss;
	_boss->setRarities(_difficulty);
}

