#pragma once
#include "Entity.h"
#include "cocos2d.h"
#include "Gear.h"
#include "Support.h"
#include "Skill.h"
#include "SkillSlash.h"
#include "SkillSwordJudgement.h"
#include "Weapon.h"

class Player : public Entity
{
protected:	
	std::vector<Gear*> _myStuff;
	std::vector<int> stats;
	std::vector<Support*> _mySupport;	
	Weapon* _weapon;
	//static Player* _instance;

public: 
	Player();
	~Player();
	//static Player* Instance();
	void levelup();
	void equip(Gear*);
	void equipWeapon(Weapon*);
	void equipSupport(Support*);
	void update();

	std::vector<Support*> getSupport();
};