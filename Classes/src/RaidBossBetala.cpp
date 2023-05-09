#include "RaidBossBetala.h"
#include "SkillSlash.h"

RaidBossBetala::RaidBossBetala(int lvl) {
	mySprite = cocos2d::Sprite::create("Sprite/betala_boss.png");
	_name = "Betala";
	_basehp = _totalHp = 5000 + 110 * lvl  ;
	_basedef = _totalDef = 200 + 20 * lvl;
	_baseMagicDef = _totalMagicDef = 200 + 10 * lvl;
	_baseatk =  _totalAtk = 100 + 67 * lvl;
	
	_lvl = lvl;
	_battleHp = _totalHp;

	SkillSlash* Slash = new SkillSlash();
	_skills.push_back(Slash);
}



