#pragma once
#include "Player.h";
class PlayerManager
{
private:
	static PlayerManager* _instance;


	Player* player;
public:
	static PlayerManager* Instance();
	void setPlayer(Player* player);
	Player* getPlayer();
};

