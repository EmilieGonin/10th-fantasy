#include "Weapon.h"


Weapon::Weapon() {
	_lvl = 1;
	_atk = 50;
	_dmgType = 0;
}

int Weapon::getAtk() { return _atk; }
int Weapon::getLvl() { return _lvl; }
int Weapon::getDmgType() { return _dmgType; }
Skill* Weapon::getSkill3() { return _skill3; }

