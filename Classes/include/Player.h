
#pragma once
#include "Entity.h"
#include "cocos2d.h"
#include "Gear.h"

class Player : public Entity
{
protected:	
	std::vector<Gear> _myStuff;
	cocos2d::Sprite* mySprite;
public: 
	Player();
	~Player();
	void levelup();
	void equip(Gear);
	void update();

	cocos2d::Sprite* getSprite();
};