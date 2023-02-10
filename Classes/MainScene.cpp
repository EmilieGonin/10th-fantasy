#include "MainScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Battle.h"
#include "MainMenuScene.h"

MainScene::MainScene() {
	srand(time(0)); //Initialize rand seed once
	_database = new Database;
	_energy = 30;
	_ready = false;
	_director = cocos2d::Director::getInstance();
	_scheduler = _director->getScheduler();

}

void MainScene::testing() { //Debug only
	
}

void MainScene::log(std::string value) {
	cocos2d::log(value.c_str());
}

void MainScene::log(int value) {
	cocos2d::log(std::to_string(value).c_str());
}

int MainScene::rand(int range) {
	int random = std::rand() % range;
	return random;
}

void MainScene::pull(int num) {
	for (size_t i = 0; i < num; i++)
	{
		int rarity = rand(1000);
		std::cout << "random : " << rarity << std::endl;

		if (rarity >= 0 && rarity < 5) {
			rarity = 3; //Legendary (0,5%)
		}
		else if (rarity >= 5 && rarity < 95) {
			rarity = 2; //Epic (9,5%)
		}
		else {
			rarity = 1; //Rare (90%)
		}

		//Vecteurs temporaires pour repr�senter la database
		//SELECT * FROM SUPPORTS WHERE RARITIES = (rarity)
		std::vector< std::vector<std::string>> database;
		std::vector<std::string> rare = { "first rare object","second rare object" ,"third rare object" ,"fourth rare object" ,"fifth rare object" };
		std::vector<std::string> epic = { "first epic object","second epic object" ,"third epic object" ,"fourth epic object" ,"fifth epic object" ,"sixth epic object" };
		std::vector<std::string> legendary = { "first legendary item", "second legendary item", "third legendary item" };
		database.push_back(rare); //0
		database.push_back(epic); //1
		database.push_back(legendary); //2

		int pull = rand(database[rarity - 1].size());
		std::cout << "Item pulled : " << database[rarity - 1][pull] << std::endl;
	}
}

//Lanc�e au d�marrage de l'application pour setup le timer
void MainScene::setTimer() {
	log("Starting timer...");
	_ready = true;
	int limit = 50; //La limite d'�nergie en fonction du niveau du joueur (database)
	clock_t start, now, timePassed;

	while (_energy < limit) { //Sera remplac� par while game is open
		if (_energy < limit) {
			start = clock();
			timePassed = 0; //Le temps du timer pr�c�dent si on a pu le stocker � la fermeture du jeu
			int duration = 3000 - timePassed; //en ms, � remplacer par 300000 (5min)

			do {
				now = clock();

				//Donn�es � stocker si on peut lancer une fonction lors de la fermeture du jeu
				timePassed = now - start;
			} while (timePassed < duration);

			_energy++;
			log("energy :");
			log(_energy);
			log("time passed");
			log(timePassed / 1000);
		}
	}
}

void MainScene::update(float delta) {
	//
}

void MainScene::signup() {
	if (!_database->checkSave()) {
		//Ajouter label cr�er un compte
		_textField = newTextField("Enter your mail");
		_textField->setPosition(center());
		this->addChild(_textField);

		Button* button = newButton("OK");
		button->setPosition(cocos2d::Vec2(centerWidth(), centerHeight()-50));
		this->addChild(button);

		Button* buttonLogin = newButton("I already have an account !");
		buttonLogin->setPosition(cocos2d::Vec2(centerWidth(), centerHeight() - 100));
		this->addChild(buttonLogin);

		button->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED) {
					cocos2d::log("ended");
					std::string input = _textField->getString();
					_database->setEmail(input);
					if (_database->createUser()) {
						_database->createSave();
						cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
					}
					else {
						this->removeChild(_textField);
						//Ajouter autres children
						signup();
					}
				}
			}
		);

		buttonLogin->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED) {
					cocos2d::log("ended");
					this->removeChild(_textField);
					//Ajouter autres children
					login();
				}
			}
		);
	}
	else {
		_database->getUser();
	}
}

void MainScene::login() {
	//Ajouter label connexion
	_textField = newTextField("Enter your mail");
	_textField->setPosition(center());
	this->addChild(_textField);

	Button* button = newButton("OK");
	button->setPosition(cocos2d::Vec2(centerWidth(), centerHeight() - 50));
	this->addChild(button);

	button->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED) {
				cocos2d::log("ended");
				std::string input = _textField->getString();
				_database->setEmail(input);
				if (_database->getUser()) {
					_database->createSave();
					cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
				}
				else {
					this->removeChild(_textField);
					//Ajouter autres children
					login();
				}
			}
		}
	);
}