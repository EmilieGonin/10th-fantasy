#pragma once

#include "cocos2d.h"
#include <vector>
#include "database.h"
#include "Interface.h"


class MainScene : public cocos2d::Scene
{
protected:
	int _energy; //Le taux d'énergie actuellement possédé par le joueur (database)
	bool _ready; //Quand l'appli est prête (loadings, testing)
	cocos2d::Director* _director;
	cocos2d::Scheduler* _scheduler;
	Database* _database;
	TextField* _textField;


public:
	MainScene();
	void update(float) override;
	void signup();
	void login();
	void testing();

	//Wrappers for cocos2d::log() function
	void log(std::string);
	void log(int);
	//Wrapper for rand() function
	int rand(int);
	//Pull the number of item wanted
	void pull(int);
	void setTimer();
};