
#pragma once
#include "Entity.h"
#include "cocos2d.h"
#include "Gear.h"
#include "Skill.h"
#include "SkillSlash.h"
#include "SkillSwordJudgement.h"
#include "Weapon.h"

class Player : public Entity
{
protected:	
	std::vector<Gear*> _myStuff;
	
	Weapon* _weapon;
	

public: 
	Player();
	~Player();
	
	void levelup();
	void equip(Gear*);
	void equipWeapon(Weapon*);
	void update();

};