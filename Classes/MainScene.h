#pragma once

#include "GameManager.h"
#include "cocos2d.h"
#include <vector>
#include "database.h"


class MainScene : public cocos2d::Scene
{
protected:
	cocos2d::Director* _director;
	Database* _database;
	GameManager* _gameManager;
	TextField* _textField; //use interface wrapper instead

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
};