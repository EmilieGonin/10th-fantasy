#include "Gear.h"

Gear::Gear(int type, int statType, int amount, int rarity, int level) {

	_type = statType;
	_statType = type;
	_amount = amount;
	_rarity = rarity;
	_level = level;	}

Gear::~Gear() {};

int Gear::getId() { return _id; }
int Gear::getType() { return _type; }
int Gear::getStatType() { return _statType; }
int Gear::getAmount() { return _amount; }
int Gear::getRarity() { return _rarity; }
int Gear::getLevel() {	return _level;	}