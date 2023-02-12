#include "SkillSwordJudgement.h"



SkillSwordJudgement::SkillSwordJudgement(){
	_name = "Judgement Sword";
	_skillSprite = cocos2d::Sprite::create("Skills/s3_sword.png");
	_maxCooldown = 4;
	_cooldown = 0;
	_multiplier = 2;
}

//void SkillSwordJudgement::additionalEffect(Entity* myCharacter, Entity* ennemy, int dmg)
//{
//	_cooldown = _maxCooldown;
//	ennemy->looseHp(dmg * 0.15);
//}