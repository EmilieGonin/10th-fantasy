#include "RaidBossShaDo.h"
#include "SkillSlash.h"

RaidBossShaDo::RaidBossShaDo(int lvl) {
	mySprite = cocos2d::Sprite::create("sprite/betala.png");
	_name = "Betala";
	_basehp = _totalHp = 6000 + 1200 * lvl;
	_baseatk = _totalAtk = 100 + 45 * lvl;
	_basedef = _totalDef = 200 + 20 * lvl;
	_baseMagicDef = _totalMagicDef = 200 + 10 * lvl;
	

	_lvl = lvl;
	_battleHp = _totalHp;

	SkillSlash* Slash = new SkillSlash();
	_skills.push_back(Slash);
}



