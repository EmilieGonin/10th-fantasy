#include "Entity.h"


Entity::Entity() {

}

Entity::~Entity() {};

int Entity::getDef() { return this->def; }
int Entity::getHp() { return this->battleHp; }
int Entity::getSpd() { return this->spd; }
int Entity::getAtk() { return this->atk; }

void Entity::looseHp(int amount) {
	this->battleHp -= amount;
}