#include "Player.h"

#include "cocos2d.h"


Player::Player(db::character* myCharacter) {
	_basehp = _totalHp = 300; // 75hp per lvl
	_basedef = _totalDef = 76; // 8 def per lvl
	_baseMagicDef = _totalMagicDef = 76; // 8 def per lvl
	_baseatk = _totalAtk = 75; // 12 atk per lvl
	_bonusMagical = _bonusPhysical = 25;
	character = myCharacter;
	_lvl = 1 ;// 50 lvl		
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


db::character* Player::getCharacter(){ return character; }

void Player::levelup() {
	_lvl += 1;
	_battleHp = _totalHp = _basehp += (75* 2 * _lvl) / 4 ;
	CCLOG("%d", _totalHp);
	_totalDef = _totalMagicDef = _basedef = _baseMagicDef += (8 * 100 + (_lvl/20) * 100) / 100;
	_totalAtk = _baseatk += (8 * 100 +(_lvl/1,5) * 100) / 100; 
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
	CCLOG(" BATTLE HPPPPPP %d", _battleHp);

	
		for (int i = 1; i < 6; i++) {
			if (character->gears[i].id != 0)
			{
				*_finalStats[character->gears[i].stat] += character->gears[i].amount;
			}
		}
	
}

std::vector<Support*> Player::getSupport() { return _mySupport; }

