#include "MainScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Battle.h"
#include "MainMenuScene.h"
#include "BattleScene.h"
#include "Interface.h"

MainScene::MainScene() {
	_database = Database::Instance();
	_gameManager = GameManager::Instance();
	_director = cocos2d::Director::getInstance();
	this->schedule(SEL_SCHEDULE(&MainScene::timer), 5); //Change to 5min!!
}

void MainScene::log(std::string value) {
	cocos2d::log(value.c_str());
}

void MainScene::log(int value) {
	cocos2d::log(std::to_string(value).c_str());
}

int MainScene::rand(int range) {
	std::random_device seed;
	std::mt19937 gen(seed());
	std::uniform_int_distribution<> distrib(1, range);
	int random = distrib(gen);

	log("range : " + std::to_string(range) + " - random : " + std::to_string(random));
	return random;
}

void MainScene::pull(int num) {
	log("**********"); //Help to see logs

	for (size_t i = 0; i < num; i++)
	{
		int rarity = rand(1000);
		std::cout << "random : " << rarity << std::endl;

		if (rarity < 5) {
			rarity = 3; //Legendary (0,5%)
		}
		else if (rarity >= 5 && rarity < 95) {
			rarity = 2; //Epic (9,5%)
		}
		else {
			rarity = 1; //Rare (90%)
		}

		db::support pulled;

		if (rarity == 3) {
			pulled = _database->getSupport(10);
		}
		else {
			std::vector<db::support> supports = _database->getSupports(rarity);
			pulled = supports[rand(supports.size()) - 1];
		}

		std::vector<int> userSupports = _database->user()->supports;
		bool alreadyPulled = std::count(userSupports.begin(), userSupports.end(), pulled.supportId);

		if (alreadyPulled) {
			//convert into currency
			_database->user()->cristals += 50 * rarity;
			log("already pulled - cristals obtained : " + std::to_string(50 * rarity));
		}
		else {
			log("new character pulled");
			_database->user()->supports.push_back(pulled.supportId);
		}

		_database->updateUser();
		log(pulled.name);
	}
}

//Lancée au démarrage de l'application pour setup le timer
void MainScene::timer(float delta) {
	int limit = 50 + ((3 * _database->user()->level) - 3);

	if (_database->isLogged() && _database->user()->energy < limit) {
		log("energy before refill : " + std::to_string(_database->user()->energy));
		_database->user()->energy++;
		_database->updateUser();
	}
}

bool MainScene::hasEnoughEnergy(int needed) {
	return _database->user()->energy >= needed;
}