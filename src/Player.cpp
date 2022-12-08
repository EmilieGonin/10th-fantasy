#include "Player.h"


Player::Player() {
	this->hp = 300; // 75hp per lvl
	this->def = 76; // 8 def per lvl
	this->atk = 100; // 12 atk per lvl
	this->lvl = 1;// 50 lvl
	this->battleHp = this->hp;
}

Player::~Player() {};

void Player::levelup() {
	this->lvl += 1;
	this->hp += 75; // 75hp per lvl
	this->def += 8; // 8 def per lvl
	this->atk += 12; // 12 atk per lvl
}

