#include "Battle.h"

Battle::Battle(Player* player, std::vector<Enemy*> enemies) {
	_player = player;
	_enemies = enemies;
	_battle = true;
	_battleOrder.push_back(_player);

	for (int i = 0; i < _enemies.size(); i++) {
		
		_battleOrder.push_back(_enemies[i]);
	}
}	

Battle::~Battle() {};

void Battle::attack(Entity* attacker, Entity* target) {

	int usedDef;
	int multiplicatorType;

	if (attacker->getDamageType() == 0) {
		usedDef = *target->getTotalStats()[PDEF];
		multiplicatorType = *attacker->getTotalStats()[PATK];
		std::cout << "Physical damage" << std::endl;
	}
	else {
		usedDef = *target->getTotalStats()[MDEF];
		multiplicatorType = *attacker->getTotalStats()[MATK];
	}
	float atk = *attacker->getTotalStats()[ATK];

	std::cout << "Damage dealt  : " << (*attacker->getTotalStats()[ATK] + (*attacker->getTotalStats()[ATK] * multiplicatorType / 100) - (usedDef / 2)) << std::endl;
	target->looseHp((*attacker->getTotalStats()[ATK] + (*attacker->getTotalStats()[ATK] * multiplicatorType / 100)  - (usedDef / 2)));
}

void Battle::turn() {
	int target;

	std::cout << "Choose an enemy : " << std::endl;
	std::cin >> target;

	attack(_player, _enemies[target-1]);
	for (int i = 0; i < _enemies.size(); i++) {
		std::cout << "Je me fiait attaquer";
		attack(_enemies[i], _player);
	}
}

void Battle::battleCheck() {
	std::cout << "MY hp status : " << _player->getBattleHP() << std::endl;
	
	for (int i = 0; i < _enemies.size(); i++) {
		
		std::cout << "Enemy n° " << i << "hp status : " << _enemies[i]->getBattleHP() << std::endl;
		if (_enemies[i]->getBattleHP() <= 0) {
			std::cout << "je delete";
			_enemies.erase(_enemies.begin() + i );
		}
	}

	if (_player->getBattleHP() > 0 && _enemies.size() >= 1) {
		_battle = true;
	}
	else if (_player->getBattleHP() <= 0) {
		_battle = false;
		_win = false;
	}
	else if (_enemies.size() == 0) {
		_battle = false;
		_win = true;
		}
}

bool Battle::getBattleState() { return _battle; }
