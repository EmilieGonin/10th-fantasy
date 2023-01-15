#include "Gear.h"

Gear::Gear(int statType, int amount) {
	_statType = statType;
	_amount = amount;
}

Gear::~Gear() {};

int Gear::getStatType() { return _statType; }
int Gear::getAmount() {	return _amount;	}