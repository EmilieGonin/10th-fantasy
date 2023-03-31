#pragma once
#include <iostream>
#include <cocos2d.h>

class Skill
{
protected:
	float _multiplier;
	std::string _description;
	cocos2d::Sequence* _skillAnim;
	cocos2d::Sprite* _skillSprite;

public:
	std::string _name;
	int _cooldown, _maxCooldown;
	Skill();

	//virtual void additionalEffect(Entity*, Entity*, int);

	float getMultiplier();
	std::string getName();
	std::string getDescription();
	cocos2d::Sequence* getSkillAnim();
	cocos2d::Sprite* getSprite();
	int getCooldown();
};