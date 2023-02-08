#include "Database.h"
#include "BattleScene.h"
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
}
void db::to_json(json& j, const user& user) {
	j = json{
		{"mail", user.mail}, {"name", user.name}, {"account_lvl", user.level},
		{"energy", user.energy}, {"cristals", user.cristals},
		{"leafs", user.leafs}, {"wishes", user.wishes},
		{"tickets", user.tickets}, {"timer", user.timer}
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
	else {
		getUser();
		cocos2d::Label* label = newLabel("Touch the screen to start");
		label->setPosition(center());

		cocos2d::Label* userLabel = newLabel("username"); //getter from database
		userLabel->setPosition(Vec2(0, 0)); //set position top

		//rajouter touch event on screen puis replace scene
		//cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
		//cocos2d::Director::getInstance()->replaceScene(BattleScene::create());
	}
}

void Database::signup() {
	//Ajouter label cr�er un compte
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
					//cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
					cocos2d::Director::getInstance()->replaceScene(BattleScene::create());
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
				_email = textField->getString();
				if (getUser()) {
					createSave();
					//cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
					cocos2d::Director::getInstance()->replaceScene(BattleScene::create());
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

bool Database::handleRequest(cpr::Response r) {
	cocos2d::log("**********"); //Help to see logs

	if (r.status_code == 0) { //Si la requ�te n'a pas pu �tre lanc�e
		cocos2d::log(r.error.message.c_str());
		cocos2d::log("**********"); //Help to see logs
		createError();
		return false;
	}
	else if (r.status_code >= 400) { //Si la requ�te a �chou�
		std::string message = std::string("Error [" + std::to_string(r.status_code) + "] making request.");
		cocos2d::log(message.c_str());
		cocos2d::log(r.text.c_str());
		cocos2d::log("**********"); //Help to see logs
		createError();
		return false;
	}
	else { //On affiche le r�sultat dans la console (debug only)
		cocos2d::log(r.text.c_str());
		cocos2d::log("**********"); //Help to see logs
		return true;
	}
}

bool Database::getUser() {
	cocos2d::log("getting user");
	std::string url = std::string(_url + "/items/users?filter[mail][_eq]=" + _email);

	if (request(url)) {
		_user = json::parse(_request.text)["data"][0].get<db::user>();
		return true;
	}
	else {
		return false;
	}
}

bool Database::createUser() {
	cocos2d::log("creating user");
	std::string url = std::string(_url + "/items/users");
	db::user user = { std::string(_email), std::string("User#" + split(_email, "@")[0]), 1, 50}; //Cr�ation de la struct
	json payload = user; //On convertis la struct en JSON

	if (request(url, payload)) {
		_user = json::parse(_request.text)["data"].get<db::user>();
		_userId = _user.id;
		url = std::string(_url + "/items/characters");
		db::character character = { _userId }; //Cr�ation de la struct
		payload = character;
		//Delete user if character isn't created
		if (request(url, payload)) {
			_character = json::parse(_request.text)["data"].get<db::character>();
			return true;
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

void Database::createError() {
	cocos2d::log("creating error");
	std::string url = std::string(_url + "/items/errors");
	db::error error = { _request.status_code, _request.error.message };
	json payload = error;
	request(url, payload);
}

void Database::setEmail(std::string email) {
	_email = email;
}

db::user Database::getUserData() { return _user; }
db::character Database::getCharacterData() { return _character; }
db::inventory Database::getInventoryData() { return _inventory; }