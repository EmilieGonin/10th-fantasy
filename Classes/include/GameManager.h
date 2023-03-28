#pragma once
#include "cocos2d.h"


class GameManager 
{
private:
	GameManager();
	static GameManager* _instance;
	
	

public:
	static GameManager* Instance();
	int BossId;
	int BossLvl;
};