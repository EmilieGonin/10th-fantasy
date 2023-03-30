#include "RaidBossBetala.h"
#include "SkillSlash.h"

RaidBossBetala::RaidBossBetala(int lvl) {
	mySprite = cocos2d::Sprite::create("sprite/betala_boss.png");
	_name = "Betala";
	_basehp = _totalHp = 5000 + 400 * lvl;
	_basedef = _totalDef = 45 + 5 * lvl;
	_baseMagicDef = _totalMagicDef = 35 + 5 * lvl;
	_baseatk =  _totalAtk = 200 + 10 * lvl;

	_lvl = lvl;// 50 lvl
	_battleHp = _totalHp;

	SkillSlash* Slash = new SkillSlash();
	_skills.push_back(Slash);
}



