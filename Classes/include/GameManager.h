#pragma once
#include "cocos2d.h"


class GameManager
{
private:
	GameManager();
	static GameManager* _instance;
	int BossId;
	int BossLvl;
	int Difficulty;
	bool _loading;
public:
	static GameManager* Instance();
	int getBossId();
	int getBossLvl();
	int getDifficulty();
	void setBossId(int);
	void setBossLvl(int);
	void setDifficulty(int);

	//Getters
	bool isLoading();

	//Setters
	void loading(bool);
};