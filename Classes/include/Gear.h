#pragma once

class Gear
{
protected:
	int _id = 0;
	int _type;
	int _statType;
	int _amount;
	int _rarity;
	int _level;

public:
	Gear(int,int, int, int, int);
	~Gear();
	int getId();
	int getType();
	int getStatType();
	int getAmount();
	int getRarity();
	int getLevel();
};