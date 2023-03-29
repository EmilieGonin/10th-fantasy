#pragma once
#include "cocos2d.h"


class GameManager
{
private:
	GameManager();
	static GameManager* _instance;
	int BossId;
	int BossLvl;
	//tuto bools
	bool TutoCompleted = false;
	int TutoPhases = 0;
public:
	static GameManager* Instance();
	//getters
	int getBossId();
	int getBossLvl();
	bool getTutoCompleted();
	int getTutoPhases();
	//setters
	void setBossId(int);
	void setBossLvl(int);
	void setTutoCompleted(bool);
	void setTutoPhases(int);


};