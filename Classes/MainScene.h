#pragma once

#include "cocos2d.h"
#include <vector>
#include "database.h"

class MainScene : public cocos2d::Scene
{
protected:
	int _energy; //Le taux d'�nergie actuellement poss�d� par le joueur (database)
	bool _ready; //Quand l'appli est pr�te (loadings, testing)
	cocos2d::Director* _director;
	cocos2d::Scheduler* _scheduler;
	Database* _database;

public:
	MainScene();
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