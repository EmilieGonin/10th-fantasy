#include "Battle.h"

Battle::Battle(Player* player, std::vector<Enemy*> enemies) {

	this->player = player;
	this->enemies = enemies;
	this->battle = true;
	this->battleOrder.push_back(this->player);
	for (int i = 0; i < enemies.size(); i++) {
		
		this->battleOrder.push_back(enemies[i]);
	}

}	

Battle::~Battle() {};

void Battle::attack(Entity* bully, Entity* target) {

	std::cout << "My hp " << target->getHp() << std::endl;
	std::cout << (bully->getAtk() - (target->getDef() / 2)) << std::endl;
	target->looseHp((bully->getAtk() - (target->getDef() / 2)));
	std::cout << "My hp " << target->getHp() << std::endl;

	
}


void Battle::turn() {
	int target;
	std::cout << "Choose an enemy : " << std::endl;
	std::cin >> target;

	this->attack(this->player, enemies[target-1]);
	for (int i = 1; i < this->enemies.size(); i++) {
		std::cout << "Je me fiait attaquer";
		this->attack(enemies[i], this->player);
	}

}
void Battle::battleCheck() {

	std::cout << "My hp : " <<  this->player->getHp() << std::endl;
	for (int i = 0; i < this->enemies.size(); i++) {
		
		std::cout << "Enemy n° " << i << "hp status : " <<  this->enemies[i]->getHp() << std::endl;
	}


	if (this->player->getHp() && this->battleOrder.size() > 1) {
		this->battle = true;
	}
	else if (this->player->getHp() <= 0) {
		this->battle = false;
		this->win = false;
	}
	else if (this->battleOrder.size() == 1) {
		this->battle = false;
		this->win = true;
		}
}


bool Battle::getBattleState() { return this->battle; }
