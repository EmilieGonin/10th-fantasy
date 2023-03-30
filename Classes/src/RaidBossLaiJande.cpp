#include "RaidBossLaiJande.h"
#include "SkillSlash.h"

RaidBossLaiJande::RaidBossLaiJande(int lvl) {
	mySprite = cocos2d::Sprite::create("sprite/betala.png");
	_name = "Betala";
	_basehp = _totalHp = 5000 + 600 * lvl;
	_baseatk = _totalAtk = 100 + 80 * lvl;
	_basedef = _totalDef = 200 + 70 * lvl;
	_baseMagicDef = _totalMagicDef = 200 + 18 * lvl;


	_lvl = lvl;
	_battleHp = _totalHp;

	SkillSlash* Slash = new SkillSlash();
	_skills.push_back(Slash);
}



