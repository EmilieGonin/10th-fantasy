#include "Player.h"

#include "cocos2d.h"

Player::Player() {
	_basehp = _totalHp = 300; // 75hp per lvl
	_basedef = _totalDef = 7.5; // 8 def per lvl
	_baseMagicDef = _totalMagicDef = 76; // 8 def per lvl
	_baseatk = _totalAtk = 75; // 12 atk per lvl
	_bonusMagical = _bonusPhysical = 1;
	_lvl = 1;// 50 lvl
	_dmgType = 0; // 
	SkillSlash *mySlash = new SkillSlash();

	_skills.push_back(mySlash);

	for (int i = 0; i < 50; i++)
	{
		levelup();
	}

	mySprite = cocos2d::Sprite::create("sprite/player.png");
	mySprite->setPosition(50, 400);
}	

Player::~Player() {};



	
void Player::levelup() {
	_lvl += 1;
	_totalHp = _basehp += 75*(_lvl/2); 
	_totalDef = _basedef += 7.5+(_lvl/5); 
	_totalMagicDef =_baseMagicDef += 8+(_lvl/20); 
	_totalAtk = _baseatk += 8+(_lvl/1,5); 
	_bonusMagical += ((_lvl / 400) / 100);
	_bonusPhysical += ((_lvl / 200) / 100);
	update();
}

void Player::equip(Gear* gear){
	_myStuff.push_back(gear);
	update();
}

void Player::equipWeapon(Weapon* weapon)
{
	_weapon = weapon;
	_totalAtk = _baseatk += _weapon->getAtk();
	_dmgType = _weapon->getDmgType();
	_skills.push_back(weapon->getSkill3());
	update();

}


void Player::equipSupport(Support* support)
{
	_mySupport.push_back(support);
}

void Player::update() {
	_battleHp = _totalHp;
	if(_myStuff.size() != 0)
	{
		for (int i = 0; i < _myStuff.size(); i++) {
			
			*_finalStats[_myStuff[i]->getGear()->stat] += _myStuff[i]->getGear()->amount;

		}
	}
}

std::vector<Support*> Player::getSupport() { return _mySupport; }

