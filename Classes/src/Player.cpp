#include "Player.h"

#include "cocos2d.h"

Player::Player() {
	_basehp = _totalHp = 300; // 75hp per lvl
	_basedef = _totalDef = 76; // 8 def per lvl
	_baseMagicDef = _totalMagicDef = 76; // 8 def per lvl
	_baseatk = _totalAtk = 75; // 12 atk per lvl
	_lvl = 1;// 50 lvl
	_dmgType = 0;

	mySprite = cocos2d::Sprite::create("sprite/player.png");
	mySprite->setPosition(50, 400);
}	

Player::~Player() {};


cocos2d::Sprite* Player::getSprite() { return mySprite; }

void Player::levelup() {
	_lvl += 1;
	_totalHp = _basehp += 75; // 75hp per lvl
	_totalDef = _basedef += 8; // 8 def per lvl
	_totalMagicDef =_baseMagicDef += 8; // 8 def per lvl
	_totalAtk = _baseatk += 20; // 12 atk per lvl
	update();
}

void Player::equip(Gear gear){
	_myStuff.push_back(gear);
	update();
}

void Player::update() {
	_battleHp = _totalHp;
	if(_myStuff.size() != 0)
	{
		for (int i = 0; i < _myStuff.size(); i++) {
			
			*_finalStats[_myStuff[i].getStatType()] = _myStuff[i].getAmount();

			std::cout << "BASE HP : " << *_baseStats[HP] << std::endl;
			std::cout << "Final HP : " << *_finalStats[HP] << std::endl;
		}
	}

	std::cout << "Final HP : " << *_finalStats[HP] << std::endl;
	std::cout << "Final DEF : " << *_finalStats[PDEF] << std::endl;
	std::cout << "Final Magical Def : " << *_finalStats[MDEF] << std::endl;
	std::cout << "Final ATK : " << *_finalStats[ATK] << std::endl;
	std::cout << "Final Physical Damage Bonus : " << *_finalStats[PATK] << std::endl;
	std::cout << "Final Magical Damage Bonus : " << *_finalStats[MATK] << std::endl;
	std::cout << "Final Crit Rate : " << *_finalStats[CR] << std::endl;
	std::cout << "Final Crit Damage : " << *_finalStats[CD] << std::endl;
}

