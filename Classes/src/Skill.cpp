#include "Skill.h"

Skill::Skill() {
	_multiplier = 1;
	_cooldown = -1;
}




float Skill::getMultiplier() { return _multiplier; }
int Skill::getCooldown() { return _cooldown; }
//void Skill::additionalEffect(Entity*, Entity*, int) { }
cocos2d::Sequence* Skill::getSkillAnim() { return _skillAnim; }
std::string Skill::getName() { return _name; }
std::string Skill::getDescription() { return _description; }
cocos2d::Sprite* Skill::getSprite() { return _skillSprite; }