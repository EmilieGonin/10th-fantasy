#pragma once
#include "Skill.h"
class Weapon
{
protected:
	int _atk, _lvl, _rarity, _dmgType;
	Skill* _skill3;
public:
	Weapon();
	int getAtk();
	int getLvl();
	int getRarity();
	int getDmgType();
	Skill* getSkill3();
};

