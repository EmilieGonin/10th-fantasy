#pragma once
#include "cocos2d.h"


class GameManager 
{
private:
	GameManager();
	static GameManager* _instance;
	int BossId;
	int BossLvl;
	

public:
	static GameManager* Instance();
};