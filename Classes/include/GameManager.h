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


	//tuto bools
	bool TutoCompleted = false;
	int TutoPhases = 0;


	bool _loading;
  
public:
	static GameManager* Instance();
	//getters
	int getBossId();
	int getBossLvl();

	int getDifficulty();
	void setBossId(int);
	void setBossLvl(int);
	void setDifficulty(int);

	bool getTutoCompleted();
	int getTutoPhases();
	//setters
	void setBossId(int);
	void setBossLvl(int);
	void setTutoCompleted(bool);
	void setTutoPhases(int);



	//Getters
	bool isLoading();

	//Setters
	void loading(bool);
};