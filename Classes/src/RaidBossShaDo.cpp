#include "RaidBossShaDo.h"
#include "SkillSlash.h"

RaidBossShaDo::RaidBossShaDo(int lvl) {
	mySprite = cocos2d::Sprite::create("Sprite/shado_boss.png");
	_name = "Sha Dô";
	_basehp = _totalHp = 3500 + 258 * lvl;
	_baseatk = _totalAtk = 100 + 155 * lvl;
	_basedef = _totalDef = 115 + 35 * lvl;
	_baseMagicDef = _totalMagicDef = 115 + 18 * lvl;
	
	_lvl = lvl;
	_battleHp = _totalHp;

	SkillSlash* Slash = new SkillSlash();
	_skills.push_back(Slash);
}