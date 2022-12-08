#include "Enemy.h"


Enemy::Enemy() {
	this->hp = 100; // 75hp per lvl
	this->def = 35; // 8 def per lvl
	this->atk = 50; // 12 atk per lvl
	this->lvl = 1;// 50 lvl
	this->battleHp = this->hp;
}

Enemy::~Enemy() {};

