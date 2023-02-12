#include "RaidBossBetala.h"
#include "SkillSlash.h"

RaidBossBetala::RaidBossBetala(int lvl) {
	mySprite = cocos2d::Sprite::create("sprite/betala.png");
	_name = "Betala";
	_basehp = _totalHp = 5000 + 400 * lvl; // 35hp per lvl
	_basedef = _totalDef = 45 + 5 * lvl; // 5 def per lvl
	_baseMagicDef = _totalMagicDef = 35 + 5 * lvl; // 5 def per lvl
	_baseatk =  _totalAtk = 200 + 10 * lvl; // 10 atk per lvl

	_lvl = lvl;// 50 lvl
	_battleHp = _totalHp;

	SkillSlash* Slash = new SkillSlash();
	_skills.push_back(Slash);
}



