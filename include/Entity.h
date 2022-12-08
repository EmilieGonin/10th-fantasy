#pragma once
class Entity
{
protected : 
	int hp, def, atk, lvl, spd;

	int battleHp;
public:
	Entity();
	~Entity();
	int getSpd();
	int getHp();
	int getDef();
	int getAtk();
	void looseHp(int);
};

