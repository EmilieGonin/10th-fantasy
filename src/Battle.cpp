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

	std::cout << "HP before attack : " << target->getHp() << std::endl;
	std::cout << "Damage dealt : " << (bully->getAtk() - (target->getDef() / 2)) << std::endl;
	target->looseHp((bully->getAtk() - (target->getDef() / 2)));
	std::cout << "HP after attack : " << target->getHp() << std::endl << std::endl;

	
}


void Battle::turn() {
	int target;
	std::cout << "Choose an enemy : " << std::endl;
	for (int i = 1; i < this->battleOrder.size(); i++) {
		std::cout << "Enemy " << i << " - hp status : " << this->battleOrder[i]->getHp() << std::endl;
	}
	std::cin >> target;


	this->attack(this->player, enemies[target-1]);
	for (int i = 1; i < this->battleOrder.size(); i++) {
		std::cout << "Enemy " << i << " attack" << std::endl;
		this->attack(battleOrder[i], this->player);
	}

}
void Battle::battleCheck() {

	std::cout << "Player HP : " <<  this->player->getHp() << std::endl;

	if (this->enemies.size()) {
		for (int i = 1; i < this->battleOrder.size(); i++) {
			if (this->battleOrder[i]->getHp() <= 0) {
				std::cout << "Enemy dead" << std::endl;
				this->battleOrder.erase(this->battleOrder.begin() + i);
				this->enemies.erase(this->enemies.begin() + i - 1);
			}
		}
	}

	std::cout << "Number of enemies : " << this->enemies.size() << std::endl;

	if (this->player->getHp() && this->enemies.size() > 0) {
		this->battle = true;
	}
	else if (!this->player->getHp()) {
		this->battle = false;
		this->win = false;
	}
	else if (!this->enemies.size()) {
		this->battle = false;
		this->win = true;
		}
}


bool Battle::getBattleState() { return this->battle; }
