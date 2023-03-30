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
	this->schedule(SEL_SCHEDULE(&MainScene::timer), 5);
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

		std::vector<db::support> supports = _database->getSupports(rarity);
		db::support pulled = supports[rand(supports.size()) - 1];

		std::vector<int> userSupports = _database->user()->supports;
		bool alreadyPulled = std::count(userSupports.begin(), userSupports.end(), pulled.supportId);

		if (alreadyPulled) {
			//convert into currency
			log("already pulled");
		}
		else {
			_database->user()->supports.push_back(pulled.supportId);
			_database->updateUser();
		}

		log(pulled.name);
	}
}

//Lancée au démarrage de l'application pour setup le timer
void MainScene::timer(float delta) {
	int limit = 50; //La limite d'énergie en fonction du niveau du joueur (database)
	log("energy");
	log(std::to_string(_database->user()->energy));

	if (_database->isLogged() && _database->user()->energy < limit) {
		_database->user()->energy++;
	}
}