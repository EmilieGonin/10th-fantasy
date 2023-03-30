#pragma once
#include "cocos2d.h"


class GameManager
{
private:
	GameManager();
	static GameManager* _instance;
	std::string bossSprites[3];
	int _bossId;
	int _bossLvl;
	int _difficulty;
	bool _tutoCompleted;
	int _tutoPhases;
	bool _loading;
  
public:
	static GameManager* Instance();

	//getters
	int getBossId();
	int getBossLvl();
	std::string getSprite();
	int getDifficulty();
	bool getTutoCompleted();
	int getTutoPhases();
	bool isLoading();

	//setters
	void setBossId(int);
	void setBossLvl(int);
	void setDifficulty(int);
	void setTutoCompleted(bool);
	void setTutoPhases(int);
	void loading(bool);
};

