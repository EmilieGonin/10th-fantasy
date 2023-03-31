#include "RaidBossShaDo.h"
#include "SkillSlash.h"

RaidBossShaDo::RaidBossShaDo(int lvl) {
	mySprite = cocos2d::Sprite::create("sprite/betala.png");
	_name = "Sha Dô";
	_basehp = _totalHp = 5000 + 600 * lvl;
	_baseatk = _totalAtk = 100 + 80 * lvl;
	_basedef = _totalDef = 200 + 70 * lvl;
	_baseMagicDef = _totalMagicDef = 200 + 18 * lvl;
	
	_lvl = lvl;
	_battleHp = _totalHp;

	SkillSlash* Slash = new SkillSlash();
	_skills.push_back(Slash);
}