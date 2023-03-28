#include "Database.h"
#include "BattleScene.h"
#include "MainMenuScene.h"
using namespace db;

//Database Structs Functions
void db::from_json(const json& j, user& user) {
	j.at("mail").get_to(user.mail);
	j.at("name").get_to(user.name);
	j.at("account_lvl").get_to(user.level);
	j.at("energy").get_to(user.energy);
	j.at("cristals").get_to(user.cristals);
	j.at("leafs").get_to(user.leafs);
	j.at("wishes").get_to(user.wishes);
	j.at("tickets").get_to(user.tickets);
	j.at("timer").get_to(user.timer);
	j.at("id").get_to(user.id);
	j.at("supports").get_to(user.supports);
}
void db::from_json(const json& j, character& character) {
	j.at("user_id").get_to(character.userId);
	j.at("level").get_to(character.level);
	j.at("head").get_to(character.head);
	j.at("chest").get_to(character.chest);
	j.at("gloves").get_to(character.gloves);
	j.at("necklace").get_to(character.necklace);
	j.at("earring").get_to(character.earring);
	j.at("ring").get_to(character.ring);
	j.at("weapon").get_to(character.weapon);
	j.at("id").get_to(character.id);
}
void db::from_json(const json& j, stat& stat) {
	j.at("id").get_to(stat.statId);
	j.at("rate").get_to(stat.rate);
	j.at("percentage").get_to(stat.percentage);
}
void db::from_json(const json& j, support& support) {
	j.at("id").get_to(support.supportId);
	j.at("name").get_to(support.name);
	j.at("rarity").get_to(support.rarity);
	j.at("type").get_to(support.type);
	j.at("stats").get_to(support.stats);
}
void db::from_json(const json& j, inventory& inventory) {
	j.at("user_id").get_to(inventory.userId);
	j.at("id").get_to(inventory.id);
}
void db::from_json(const json& j, gear& gear) {
	j.at("type").get_to(gear.type);
	j.at("stat").get_to(gear.stat);
	j.at("amount").get_to(gear.amount);
	j.at("rarity").get_to(gear.rarity);
	j.at("level").get_to(gear.level);
}
void db::to_json(json& j, const user& user) {
	j = json{
		{"mail", user.mail}, {"name", user.name}, {"account_lvl", user.level},
		{"energy", user.energy}, {"cristals", user.cristals},
		{"leafs", user.leafs}, {"wishes", user.wishes},
		{"tickets", user.tickets}, {"timer", user.timer},
		{"supports", user.supports}
	};
}
void db::to_json(json& j, const character& character) {
	j = json{
		{"user_id", character.userId}, {"level", character.level},
		{"head", character.head}, {"chest", character.chest},
		{"gloves", character.gloves}, {"necklace", character.necklace},
		{"earring", character.earring}, {"ring", character.ring},
		{"weapon", character.weapon}
	};
}
void db::to_json(json& j, const inventory& inventory) {
	j = json{
		{"user_id", inventory.userId}
	};
}
void db::to_json(json& j, const gear& gear) {
	j = json{
		{"type", gear.type}, {"stat", gear.stat},
		{"amount", gear.amount}, {"rarity", gear.rarity},
		{"level", gear.level}
	};
}
void db::to_json(json& j, const error& error) {
	j = json{
		{"code", error.code}, {"message", error.message},
		{"user_id", error.userId}
	};
}

//Database Class Functions
Database* Database::_instance = new Database();

Database::Database() {
	_url = "https://49g5s1t0.directus.app"; //To encrypt
}

Database* Database::Instance() {
	return _instance;
}

void Database::init(cocos2d::Scene* scene) {
	setScene(scene);

	if (!checkSave()) {
		signup();
	}
	else if (getUser()) {
		cocos2d::Label* label = newLabel("Touch the screen to start", 1);
		label->setPosition(center());

		cocos2d::Label* userLabel = newLabel("username", 1); //getter from database
		userLabel->setPosition(Vec2(0, 0)); //set position top

		Button* button = newButton("Next");
		button->setPosition(cocos2d::Vec2(centerWidth(), centerHeight() - 50));

		button->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED) {
					cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
				}
			}
		);
		//rajouter touch event on screen puis replace scene
		//cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
		//cocos2d::Director::getInstance()->replaceScene(BattleScene::create());
	}
	else {
		deleteSave();
		init(scene);
	}
}

void Database::signup() {
	//Ajouter label créer un compte
	TextField* textField = newTextField("Enter your mail");
	textField->setPosition(center());

	Button* button = newButton("OK");
	button->setPosition(cocos2d::Vec2(centerWidth(), centerHeight() - 50));

	Button* buttonLogin = newButton("I already have an account !");
	buttonLogin->setPosition(cocos2d::Vec2(centerWidth(), centerHeight() - 100));

	button->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED) {
				cocos2d::log("button endend");
				_email = _textFields[0]->getString();
				if (createUser()) {
					createSave();
					cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
				}
				else {
					clean();
					signup();
				}
			}
		}
	);

	buttonLogin->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED) {
				clean();
				login();
			}
		}
	);
}

void Database::login() {
	//Ajouter label connexion
	TextField* textField = newTextField("Enter your mail");
	textField->setPosition(center());

	Button* button = newButton("OK");
	button->setPosition(cocos2d::Vec2(centerWidth(), centerHeight() - 50));

	button->addTouchEventListener([&](cocos2d::Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED) {
				_email = _textFields[0]->getString();
				if (getUser()) {
					createSave();
					cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
				}
				else {
					clean();
					login();
				}
			}
		}
	);
}

bool Database::checkSave() {
	bool dataFound = false;
	std::ifstream file("user.txt");

	if (file.is_open()) {
		cocos2d::log("file opened");
		std::string line;
		do {
			if (!line.empty()) {
				std::vector<std::string> data = split(line, "=");

				if (data[0] == "User") {
					_email = data[1];
					cocos2d::log("user data found");
					dataFound = true;
				}
			}
		} while (std::getline(file, line));
	}

	file.close();
	return dataFound;
}

void Database::createSave() {
	std::ofstream file("user.txt");
	file << "User=" + _email << std::endl;
	file.close();
}

void Database::deleteSave() {
	remove("user.txt");
}

std::vector<std::string> Database::split(std::string string, std::string delim) {
	std::size_t delimIndex = string.find(delim);
	std::string setting = string.substr(0, delimIndex);
	std::string value = string.substr(delimIndex + 1);

	std::vector<std::string> data = { setting, value };
	return data;
}

bool Database::request(std::string url) {
	_request = cpr::Get(cpr::Url{ url }, cpr::VerifySsl{ false });
	return handleRequest(_request);
}

bool Database::request(std::string url, json payload) {
	_request = cpr::Post(
		cpr::Url{ url }, cpr::VerifySsl{ false },
		cpr::Body{ payload.dump() },
		cpr::Header{ {"Content-Type", "application/json"} });

	return handleRequest(_request);
}

bool Database::patch(std::string url, json payload) {
	_request = cpr::Patch(
		cpr::Url{ url }, cpr::VerifySsl{ false },
		cpr::Body{ payload.dump() },
		cpr::Header{ {"Content-Type", "application/json"} });

	return handleRequest(_request);
}

bool Database::handleRequest(cpr::Response r) {
	cocos2d::log("**********"); //Help to see logs
	json request = json::parse(r.text)["data"];

	if (r.status_code == 0) { //Si la requête n'a pas pu être lancée
		cocos2d::log(r.error.message.c_str());
		cocos2d::log("**********"); //Help to see logs
		createError();
		return false;
	}
	else if (r.status_code >= 400) { //Si la requête a échoué
		std::string message = std::string("Error [" + std::to_string(r.status_code) + "] making request.");
		cocos2d::log(message.c_str());
		cocos2d::log(r.text.c_str());
		cocos2d::log("**********"); //Help to see logs
		createError();
		return false;
	}
	else if (request.empty()) {
		cocos2d::log("Data received are empty !");
		return false;
	}
	else { //On affiche le résultat dans la console (debug only)
		cocos2d::log(r.text.c_str());
		cocos2d::log("**********"); //Help to see logs
		return true;
	}
}

bool Database::getUser() {
	std::string url = std::string(_url + "/items/users?filter[mail][_eq]=" + _email);

	if (request(url)) {
		_user = json::parse(_request.text)["data"][0].get<db::user>();
		if (getCharacter()) {
			return getInventory();
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Database::getCharacter() {
	std::string url = std::string(_url + "/items/characters?filter[user_id][_eq]=" + std::to_string(_user.id));

	if (request(url)) {
		_character = json::parse(_request.text)["data"][0].get<db::character>();
		return true;
	}
	else {
		return false;
	}
}

bool Database::getInventory() {
	std::string url = std::string(_url + "/items/inventories?filter[user_id][_eq]=" + std::to_string(_user.id));

	if (request(url)) {
		_inventory = json::parse(_request.text)["data"][0].get<db::inventory>();
		return true;
	}
	else {
		return false;
	}
}

bool Database::createUser() {
	std::string url = std::string(_url + "/items/users");
	db::user user = { std::string(_email), std::string("User#" + split(_email, "@")[0]), 1, 50}; //Création de la struct
	json payload = user; //On convertis la struct en JSON

	if (request(url, payload)) { //Création de l'utilisateur
		_user = json::parse(_request.text)["data"].get<db::user>();
		//Delete user if character isn't created
		if (createCharacter()) { //Création du personnage
			return createInventory(); //Création de l'inventaire
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	//Clean even if true
}

bool Database::createCharacter() {
	std::string url = std::string(_url + "/items/characters");
	db::character character = { _user.id }; //Création de la struct
	json payload = character;

	if (request(url, payload)) {
		_character = json::parse(_request.text)["data"].get<db::character>();
		return true;
	}
	else {
		return false;
	}
}

bool Database::createInventory() {
	std::string url = std::string(_url + "/items/inventories");
	db::inventory inventory = { _user.id }; //Création de la struct
	json payload = inventory;

	if (request(url, payload)) {
		_inventory = json::parse(_request.text)["data"].get<db::inventory>();
		return true;
	}
	else {
		return false;
	}
}

void Database::createError() {
	cocos2d::log("creating error");
	std::string url = std::string(_url + "/items/errors");
	db::error error = { _request.status_code, _request.text, _user.id ? _user.id : 0 };
	json payload = error;
	request(url, payload);
}

bool Database::update() {
	if (!updateUser() || !updateCharacter() || !updateInventory()) {
		return false;
	}
	else {
		return true;
	}
}

bool Database::updateUser() {
	std::string url = std::string(_url + "/items/users/" + std::to_string(_user.id));
	json payload = _user;
	return patch(url, payload);
}

bool Database::updateCharacter() {
	std::string url = std::string(_url + "/items/characters/" + std::to_string(_character.id));
	json payload = _character;
	return patch(url, payload);
}

bool Database::updateInventory() {
	std::string url = std::string(_url + "/items/inventories/" + std::to_string(_inventory.id));
	json payload = _inventory;
	return patch(url, payload);
}

void Database::setEmail(std::string email) {
	_email = email;
}

db::user* Database::user() { return &_user; }
db::character* Database::character() { return &_character; }
db::inventory* Database::inventory() { return &_inventory; }