#include "SkillSlash.h"


SkillSlash::SkillSlash(){
	_name = "Slash";
	_skillSprite = cocos2d::Sprite::create("Skills/s1_sword.png");
	_maxCooldown = _cooldown = 0;
}
