#pragma once
#include "Entity.h"
#include "cocos2d.h"
#include "Gear.h"
#include "Database.h"
#include "Support.h"
#include "Skill.h"
#include "SkillSlash.h"
#include "SkillSwordJudgement.h"
#include "Weapon.h"

class Player : public Entity
{
protected:	
	db::character* character;
	std::vector<int> stats;
	std::vector<Support*> _mySupport;	
	Weapon* _weapon;
public: 
	Player(db::character*);
	~Player();
	db::character* getCharacter();
	void levelup();
	void equipWeapon(Weapon*);
	void equipSupport(Support*);
	void update();

	std::vector<Support*> getSupport();
};