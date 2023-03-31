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
	j.at("exp").get_to(user.exp);
	j.at("cristals").get_to(user.cristals);
	j.at("leafs").get_to(user.leafs);
	j.at("wishes").get_to(user.wishes);
	j.at("tickets").get_to(user.tickets);
	j.at("timer").get_to(user.timer);
	j.at("id").get_to(user.id);
	j.at("supports").get_to(user.supports);
	j.at("gender").get_to(user.gender);
	j.at("tutorial").get_to(user.tutorial);
}
void db::from_json(const json& j, character& character) {
	j.at("user_id").get_to(character.userId);
	j.at("gears_id").get_to(character.gearsId);
	j.at("supports_id").get_to(character.supportsId);
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
	j.at("inventory_id").get_to(gear.inventoryId);
}
void db::to_json(json& j, const user& user) {
	j = json{
		{"mail", user.mail}, {"name", user.name}, {"account_lvl", user.level},
		{"energy", user.energy}, {"cristals", user.cristals}, {"exp", user.exp},
		{"leafs", user.leafs}, {"wishes", user.wishes},
		{"tickets", user.tickets}, {"timer", user.timer},
		{"supports", user.supports}, {"gender", user.gender},
		{"tutorial", user.tutorial}
	};
}
void db::to_json(json& j, const character& character) {
	j = json{
		{"user_id", character.userId}, {"gears_id", character.gearsId},
		{"supports_id", character.supportsId}
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
		{"level", gear.level}, {"inventory_id", gear.inventoryId}
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
	_logged = false;
}

Database* Database::Instance() {
	return _instance;
}

void Database::init(cocos2d::Scene* scene) {
	setScene(scene);
	_gameManager = GameManager::Instance();

	if (!checkSave()) {
		signup();
	}
	else if (getUser()) {
		cocos2d::Label* label = newOutlinedLabel("Touch the screen to start");
		label->setPosition(center());

		cocos2d::Label* userLabel = newOutlinedLabel("Logged in as " + _user.name);
		userLabel->setPosition(Vec2(centerWidth(), top(userLabel->getLineHeight())));
	}
	else {
		logout(scene);
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

void Database::logout(cocos2d::Scene* scene) {
	_logged = false;
	clean();
	deleteSave();
	init(scene);
}

bool Database::checkSave() {
	_gameManager->loading(true);
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
	_gameManager->loading(false);
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
	_gameManager->loading(true);
	_request = cpr::Get(cpr::Url{ url }, cpr::VerifySsl{ false });
	return handleRequest();
}

bool Database::request(std::string url, json payload) {
	_gameManager->loading(true);
	_request = cpr::Post(
		cpr::Url{ url }, cpr::VerifySsl{ false },
		cpr::Body{ payload.dump() },
		cpr::Header{ {"Content-Type", "application/json"} });

	return handleRequest();
}

bool Database::patch(std::string url, json payload) {
	_gameManager->loading(true);
	_request = cpr::Patch(
		cpr::Url{ url }, cpr::VerifySsl{ false },
		cpr::Body{ payload.dump() },
		cpr::Header{ {"Content-Type", "application/json"} });

	return handleRequest();
}

bool Database::deleteRequest(std::string url) {
	_gameManager->loading(true);
	_request = cpr::Delete(cpr::Url{ url }, cpr::VerifySsl{ false });
	return handleRequest();
}

bool Database::handleRequest() {
	_gameManager->loading(false);
	cocos2d::log("**********"); //Help to see logs
	json request = json::parse(_request.text)["data"];

	if (_request.status_code == 0) { //Si la requête n'a pas pu être lancée
		cocos2d::log(_request.error.message.c_str());
		cocos2d::log("**********"); //Help to see logs
		createError();
		return false;
	}
	else if (_request.status_code >= 400) { //Si la requête a échoué
		std::string message = std::string("Error [" + std::to_string(_request.status_code) + "] making request.");
		cocos2d::log(message.c_str());
		cocos2d::log(_request.text.c_str());
		cocos2d::log("**********"); //Help to see logs
		createError();
		return false;
	}
	else if (request.empty()) {
		cocos2d::log("Data received are empty !");
		return false;
	}
	else { //On affiche le résultat dans la console (debug only)
		cocos2d::log(_request.text.c_str());
		cocos2d::log("**********"); //Help to see logs
		return true;
	}
}

bool Database::getUser() {
	std::string url = std::string(_url + "/items/users?filter[mail][_eq]=" + _email);

	if (request(url)) {
		_user = json::parse(_request.text)["data"][0].get<db::user>();
		if (getCharacter()) {
			_logged = true;
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

		//Getting character gears
		for (size_t i = 0; i < std::size(_character.gearsId); i++)
		{
			int id = _character.gearsId[i];

			if (id) {
				url = std::string(_url + "/items/gears/" + std::to_string(id));

				if (request(url)) {
					db::gear gear = json::parse(_request.text)["data"][0].get<db::gear>();
					_character.gears[gear.type] = gear;
				}
			}
		}

		//Getting character supports
		for (size_t i = 0; i < std::size(_character.supportsId); i++)
		{
			int id = _character.supportsId[i];

			if (id) {
				db::support support = getSupport(id);
				_character.supports[i] = support;
			}
		}

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

		//Getting inventory gears
		url = std::string(_url + "/items/gears?filter[inventory_id][_eq]=" + std::to_string(_inventory.id));

		if (request(url)) {
			json data = json::parse(_request.text)["data"];

			for (auto& elem : data) {
				_inventory.gears.push_back(elem.get<db::gear>());
			}
		}

		return true;
	}
	else {
		return false;
	}
}

bool Database::createUser() {
	std::string url = std::string(_url + "/items/users");
	db::user user = { std::string(_email), std::string("User#" + split(_email, "@")[0]), 1, 50, 1000}; //Création de la struct
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

	for (size_t i = 0; i < std::size(character.gearsId); i++)
	{
		character.gearsId[i] = 0;
	}

	for (size_t i = 0; i < std::size(character.supportsId); i++)
	{
		character.supportsId[i] = 0;
	}

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

bool Database::createGear(db::gear gear) {
	std::string url = std::string(_url + "/items/gears");
	gear.inventoryId = _inventory.id;
	json payload = gear;

	if (request(url, payload)) {
		_inventory.gears.push_back(json::parse(_request.text)["data"].get<db::gear>());
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

bool Database::updateGear(int index) {
	std::string url = std::string(_url + "/items/gears/" + std::to_string(_inventory.gears[index].id));
	json payload = _inventory.gears[index];
	return patch(url, payload);
}

bool Database::deleteUser() {
	std::string url = std::string(_url + "/items/users/" + std::to_string(_user.id));
	return deleteRequest(url);
}

bool Database::deleteGear(int index) {
	std::string url = std::string(_url + "/items/gears/" + std::to_string(_inventory.gears[index].id));
	_inventory.gears.erase(_inventory.gears.begin() + index);
	return deleteRequest(url);
}

void Database::setGear(db::gear gear) {
	_character.gears[gear.type] = gear;
	_character.gearsId[gear.type] = gear.id;
	updateCharacter();
}

void Database::setSupport(db::support support, int index) {
	_character.supports[index] = support;
	_character.supportsId[index] = support.supportId;
	updateCharacter();
}

std::vector<db::support> Database::getSupports(int rarity) {
	_gameManager->loading(true);
	std::string file = FileUtils::getInstance()->getStringFromFile("Database/supports.json");
	json data = json::parse(file);
	std::vector<db::support> supports;

	for (auto& elem : data) {
		db::support support = elem.get<db::support>();

		if (support.rarity == rarity) {
			supports.push_back(support);
		}
	}

	_gameManager->loading(false);
	return supports;
}

db::support Database::getSupport(int index) {
	_gameManager->loading(true);
	std::string file = FileUtils::getInstance()->getStringFromFile("Database/supports.json");
	db::support support = json::parse(file)[index - 1 ].get<db::support>();
	_gameManager->loading(false);
	return support;
}

/*Supports comment
  Rarities :
  1 = Rare, 2 = Epic, 3 = Legendary

  Type :
  1 = Healer, 2 = Buffer, 3 = Sub DPS

  Stats :
  1 = HP, 2 = DEF, 3 = Magic Def, 4 = ATK
  5 = Speed, 6 = Critical Rate, 7 = Critical Damage
  8 = Physical Bonus, 9 = Magical Bonus,
  10 = Same Phy/Mag Bonus, 11 = Reverse Phy/Mag Bonus,
  12 = Reduce Damage, 13 = Shield,
  14 = Ignore Defense
  */

void Database::setEmail(std::string email) { _email = email; }
void Database::emptyPull() { _lastPull.clear(); }

db::user* Database::user() { return &_user; }
db::character* Database::character() { return &_character; }
db::inventory* Database::inventory() { return &_inventory; }
std::vector<db::support>* Database::lastPull() { return &_lastPull; }
bool Database::isLogged() { return _logged; }