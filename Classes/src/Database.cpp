#include "Database.h"
#include "BattleScene.h"
using namespace db;

//Database Structs Functions
void db::from_json(const json& j, user& user) {
	j.at("id").get_to(user.id);
	j.at("mail").get_to(user.mail);
	j.at("name").get_to(user.name);
}
void db::from_json(const json& j, character& character) {
	j.at("user_id").get_to(character.userId);
}
void db::to_json(json& j, const user& user) {
	j = json{ {"mail", user.mail }, {"name", user.name } };
}
void db::to_json(json& j, const character& character) {
	j = json{ {"user_id", character.userId} };
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

	if (r.status_code == 0) { //Si la requête n'a pas pu être lancée
		cocos2d::log(r.error.message.c_str());
		cocos2d::log("**********"); //Help to see logs
		return false;
	}
	else if (r.status_code >= 400) { //Si la requête a échoué
		std::string message = std::string("Error [" + std::to_string(r.status_code) + "] making request.");
		cocos2d::log(message.c_str());
		cocos2d::log(r.text.c_str());
		cocos2d::log("**********"); //Help to see logs
		return false;
	}
	else { //On affiche le résultat dans la console (debug only)
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
	db::user user = { std::string(_email), std::string("User#" + split(_email, "@")[0])}; //Création de la struct
	json payload = user; //On convertis la struct en JSON

	if (request(url, payload)) {
		_user = json::parse(_request.text)["data"].get<db::user>();
		_userId = _user.id;
		url = std::string(_url + "/items/characters");
		db::character character = { _userId }; //Création de la struct
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

void Database::createSave() {
	std::ofstream file("user.txt");
	file << "User=" + _email << std::endl;
	file.close();
}

void Database::setEmail(std::string email) {
	_email = email;
}

db::user Database::getUserData() { return _user; }
db::character Database::getCharacterData() { return _character; }
db::inventory Database::getInventoryData() { return _inventory; }