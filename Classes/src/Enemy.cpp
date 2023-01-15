#include "Enemy.h"

Enemy::Enemy(int lvl) {
	_basehp, _totalHp = 100 + 35*lvl ; // 35hp per lvl
	_basedef, _totalDef = 35 + 5 * lvl; // 5 def per lvl
	_baseMagicDef, _totalMagicDef = 35 + 5 * lvl; // 5 def per lvl
	_baseatk, _totalAtk = 50 + 10*lvl; // 10 atk per lvl
	_lvl = lvl;// 50 lvl
	_battleHp = _totalHp;

	std::cout << _finalStats[0];
}

Enemy::~Enemy() {};

