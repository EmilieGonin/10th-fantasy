#pragma once
#include "cocos2d.h"


class GameManager
{
private:
	GameManager();
	static GameManager* _instance;
	int BossId;
	int BossLvl;
	bool _loading;
public:
	static GameManager* Instance();
	int getBossId();
	int getBossLvl();
	void setBossId(int);
	void setBossLvl(int);

	//Getters
	bool isLoading();

	//Setters
	void loading(bool);
};