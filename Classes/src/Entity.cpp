#include "Entity.h"

Entity::Entity() {
	_bonusPhysical, _totalPhysicalBonus = 0;
	_bonusMagical, _totalMagicalBonus = 0;

	_baseStats.push_back(&_baseatk);
	_baseStats.push_back(&_bonusMagical);

	_baseStats.push_back(&_bonusPhysical);
	_baseStats.push_back(&_baseMagicDef);
	_baseStats.push_back(&_basedef);
	_baseStats.push_back(&_basehp);
	_baseStats.push_back(&_critRate);
	_baseStats.push_back(&_critDamage);

	_finalStats.push_back(&_totalAtk);
	_finalStats.push_back(&_totalMagicalBonus);
	_finalStats.push_back(&_totalPhysicalBonus);
	_finalStats.push_back(&_totalMagicDef);
	_finalStats.push_back(&_totalDef);
	_finalStats.push_back(&_totalHp);
	_finalStats.push_back(&_totalCritRate);
	_finalStats.push_back(&_totalCritDamage);
}

Entity::~Entity() {};

int Entity::getSpd() { return _spd; }
int Entity::getBattleHP() { return _battleHp; }
int Entity::getDamageType() { return _dmgType; }
std::vector<Skill*> Entity::getSkills() { return _skills; }
std::vector<int*> Entity::getBaseStats() { return _baseStats; }
std::vector<int*> Entity::getTotalStats() { return _finalStats; }

cocos2d::Sprite* Entity::getSprite() { return mySprite; }

void Entity::looseHp(int amount) {
	_battleHp -= amount;
	if (_battleHp < 0)
	{
		_battleHp = 0;
	}
}

void Entity::setBattleHp(int hp) { _battleHp = hp; }