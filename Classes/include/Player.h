#pragma once
#include "Entity.h"
#include "Gear.h"

class Player : public Entity
{
protected:	
	std::vector<Gear> _myStuff;

public: 
	Player();
	~Player();
	void levelup();
	void equip(Gear);
	void update();
};