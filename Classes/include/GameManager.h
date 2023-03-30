#pragma once
#include "cocos2d.h"
#include "RaidBoss.h"

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
	RaidBoss* _boss;
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
	RaidBoss* getBoss();

	//setters
	void setBossId(int);
	void setBossLvl(int);
	void setDifficulty(int);
	void setTutoCompleted(bool);
	void setTutoPhases(int);
	void loading(bool);

	void setBoss(RaidBoss*);

	enum Stats {
		ATK = 0,
		MATK = 1,
		PATK = 2,
		MDEF = 3,
		PDEF = 4,
		HP = 5,
		CR = 6,
		CD = 7,
		SPEED = 8
	};

	enum Stuff {
		WEAPON = 0,
		HELMET = 1,
		CHEST = 2,
		BOOT = 3,
		RING = 4,
		EARRING = 5,
		NECKLACE = 6,
	};

	enum Rarity {
		COMMON = 0,
		RARE = 1,
		EPIC = 2,
		LEGENDARY = 3,
	};

};

