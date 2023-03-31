#pragma once

#include "GameManager.h"
#include "PlayerManager.h"
#include "cocos2d.h"
#include <vector>
#include "database.h"


class MainScene : public cocos2d::Scene, public Interface
{
protected:
	cocos2d::Director* _director;
	Database* _database;
	GameManager* _gameManager;
	PlayerManager* _playerManager;
	TextField* _textField; //use interface wrapper instead
	DrawNode* _loadingRect;
	Label* _loadingLabel;

public:
	MainScene();

	//Wrappers for cocos2d::log() function
	void log(std::string);
	void log(int);
	//Wrapper for rand() function
	int rand(int);
	//Pull the number of item wanted
	void pull(int);
	void timer(float);
	bool hasEnoughEnergy(int);
	bool hasEnoughCristals(int);
	void loadingScreen();
	void stopLoadingScreen();
};