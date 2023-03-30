#pragma once
#include "cocos2d.h"


class GameManager
{
private:
	GameManager();
	static GameManager* _instance;
	int BossId;
	int BossLvl;
	std::string bossSprites[3];

public:
	static GameManager* Instance();
	int getBossId();
	int getBossLvl();
	std::string getSprite();

	void setBossId(int);
	void setBossLvl(int);
};	