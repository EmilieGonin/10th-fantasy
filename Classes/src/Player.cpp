#include "Player.h"

#include "cocos2d.h"


Player::Player(db::user* character) {
	_basehp = _totalHp = 300; // 75hp per lvl
	_basedef = _totalDef = 76; // 8 def per lvl
	_baseMagicDef = _totalMagicDef = 76; // 8 def per lvl
	_baseatk = _totalAtk = 98; // 12 atk per lvl
	_bonusMagical = _bonusPhysical = 25;
	_critRate = _totalCritRate = 15;
	_critDamage = _totalCritDamage = 100;
	_lvl = 1;// 50 lvl		
	_dmgType = 0; // 
	SkillSlash *mySlash = new SkillSlash();
	mySprite = Sprite::create("Sprite/player.png");
	mySprite->setPosition(50, 400);

	_character = character;
		

	_skills.push_back(mySlash);

	for (int i = 0; i < _character->level; i++)
	{
		levelup();
	}

	update();
}	

Player::~Player() {};


db::user* Player::getCharacter(){ return _character; }

void Player::levelup() {
	_lvl += 1;
	_battleHp = _totalHp = _basehp += (75* 2 * _lvl) / 4 ;
	CCLOG("%d", _totalHp);
	_totalDef = _totalMagicDef = _basedef = _baseMagicDef += (8 * 100 + (_lvl/20) * 100) / 100;
	_totalAtk = _baseatk += (8 * 100 +(_lvl/1,5) * 100) / 100; 

}

void Player::equip(db::gear gear){
	_character->gears[gear.type] = gear.id;
	Database::Instance()->updateUser();
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
	//CCLOG("STUFF SIZE %d", _myStuff.size());
	CCLOG(" BATTLE HPPPPPP %d", _battleHp);
	_battleHp = _totalHp;
	for each (int gear in _character->gears)
	{
		if (gear != 0)
		{
			CCLOG("Stat added");
			*_finalStats[Database::Instance()->gears()[0][gear-1].stat] += Database::Instance()->gears()[0][gear-1].amount;
		}
	}
}


void Player::unequip(db::gear gear) {
	_character->gears[gear.type] = 0;
	Database::Instance()->updateUser();
	update();
}




std::vector<Support*> Player::getSupport() { return _mySupport; }
