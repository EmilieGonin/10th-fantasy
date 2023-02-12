#include "Sword.h"


Sword::Sword(int lvl)
{
	_lvl = 50;
	_atk = 50 + 7 * lvl;
	_dmgType = 0;
	SkillSwordJudgement* s3 = new SkillSwordJudgement();
	_skill3 = s3;
}