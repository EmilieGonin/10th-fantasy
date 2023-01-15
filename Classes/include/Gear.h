#pragma once

class Gear
{
protected:
	int _statType;
	int _amount;

public:
	Gear(int,int);
	~Gear();

	int getStatType();
	int getAmount();
};