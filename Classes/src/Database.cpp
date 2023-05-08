#include "Database.h"
#include "BattleScene.h"
#include "MainMenuScene.h"
using namespace db;

//Database Structs Functions
void db::from_json(const json& j, user& user) {
	j.at("Energy").get_to(user.energy);
	j.at("Cristals").get_to(user.cristals);
	j.at("Gender").get_to(user.gender);
	j.at("Tutorial").get_to(user.tutorial);
	j.at("Level").get_to(user.level);
	j.at("Experience").get_to(user.exp);
	j.at("Gears").get_to(user.gears);
}
void db::from_json(const json& j, character& character) {
	j.at("user_id").get_to(character.userId);
	j.at("level").get_to(character.level);
	j.at("exp").get_to(character.exp);
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
	j.at("id").get_to(gear.id);
}
void db::to_json(json& j, const user& user) {
	j = json{
		{"Energy", user.energy}, {"Cristals", user.cristals},
		{"Gender", user.gender}, {"Tutorial", user.tutorial},
		{"Level", user.level}, {"Experience", user.exp},
		{"Gears", user.gears}
	};
}
void db::to_json(json& j, const character& character) {
	j = json{
		{"user_id", character.userId}, {"level", character.level},
		{"exp", character.exp}, {"gears_id", character.gearsId},
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
		{"level", gear.level}, {"id", gear.id}
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
	//PlayFab Setup
	_id = "E44FB";
	_password = "TemporaryPassword";
	_logged = false;

	PlayFab::PlayFabSettings::titleId = _id;
}

Database* Database::Instance() {
	return _instance;
}

//Wrappers

std::vector<std::string> Database::split(std::string string, std::string delim) {
	std::size_t delimIndex = string.find(delim);
	std::string setting = string.substr(0, delimIndex);
	std::string value = string.substr(delimIndex + 1);

	std::vector<std::string> data = { setting, value };
	return data;
}

std::string Database::createUsername() {
	std::string name = split(_email, "@")[0];
	std::string username;

	for (size_t i = 0; i < name.length(); i++)
	{
		if (isalpha(name[i])) {
			username += name[i];
		}
	}

	return username;
}

void Database::setEntityKey(PlayFab::ClientModels::EntityTokenResponse* token) {
	_token = token;

	PlayFab::PlayFabSettings::entityToken = _token->EntityToken;

	_setObjectsRequest = PlayFab::DataModels::SetObjectsRequest();
	_setObjectsRequest.Entity.Id = _token->Entity->Id;
	_setObjectsRequest.Entity.Type = _token->Entity->Type;

	_getObjectsRequest = PlayFab::DataModels::GetObjectsRequest();
	_getObjectsRequest.Entity.Id = _token->Entity->Id;
	_getObjectsRequest.Entity.Type = _token->Entity->Type;
	_getObjectsRequest.EscapeObject = true;
}

//Pour vérifier les données au lancement du jeu

void Database::init(cocos2d::Scene* scene) {
	_gameManager = GameManager::Instance();
	_scene = scene;
	setScene(_scene);

	if (!checkSave()) {
		signup();
	}
	else {
		getUser();
	}
}

bool Database::checkSave() {
	_gameManager->loading(true);
	_hasSave = false;
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
					_hasSave = true;
				}
			}
		} while (std::getline(file, line));
	}

	file.close();
	_gameManager->loading(false);
	return _hasSave;
}

void Database::createSave() {
	std::ofstream file("user.txt");
	file << "User=" + _email << std::endl;
	file.close();

	cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
}

void Database::deleteSave() {
	remove("user.txt");
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
				createUser();
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
				getUser();
				/*if (getUser()) {
					createSave();
					cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
				}
				else {
					clean();
					login();
				}*/
			}
		}
	);
}

void Database::logout() {
	_logged = false;
	clean();
	deleteSave();
	init(_scene);
}

//PlayFab callbacks - register

void Database::OnRegisterRequestSuccess(const PlayFab::ClientModels::RegisterPlayFabUserResult& result, void*) {
	cocos2d::log("register success");
	_instance->setEntityKey(result.EntityToken);
	_instance->update();
}

void Database::OnSetObjectsRequestSuccess(const PlayFab::DataModels::SetObjectsResponse& response, void*) {
	cocos2d::log("objects set success");

	if (!_instance->_hasSave) {
		_instance->createSave();
	}
}

void Database::OnRegisterRequestError(const PlayFab::PlayFabError& error, void* customData) {
	OnRequestError(error, customData);
	_instance->clean();
	_instance->signup();
}

//PlayFab callbacks - login

void Database::OnLoginRequestSuccess(const PlayFab::ClientModels::LoginResult& result, void*) {
	cocos2d::log("login success");
	_instance->setEntityKey(result.EntityToken);
	_instance->_username = result.InfoResultPayload->PlayerProfile->DisplayName;

	PlayFab::PlayFabDataAPI::GetObjects(_instance->_getObjectsRequest, OnGetObjectsRequestSuccess, OnRequestError, nullptr);
}

void Database::OnGetObjectsRequestSuccess(const PlayFab::DataModels::GetObjectsResponse& response, void*) {
	cocos2d::log("objects get success");
	json playerData = json::parse(response.Objects.at("PlayerData").EscapedDataObject);
	json playerGears = json::parse(response.Objects.at("PlayerGears").EscapedDataObject);
	_instance->_user = playerData.get<db::user>();

	for (auto& elem : playerGears) {
		_instance->_gears.push_back(elem.get<db::gear>());
	}

	/*db::gear gear = {
		1, 1, 1, 1, 1, 1
	};

	_instance->createGear(gear);
	_instance->setGear(gear);*/

	_instance->_logged = true;

	if (_instance->_hasSave) {
		cocos2d::Label* label = _instance->newOutlinedLabel("Touch the screen to start");
		label->setPosition(_instance->center());

		cocos2d::Label* userLabel = _instance->newOutlinedLabel("Logged in as " + _instance->_username);
		userLabel->setPosition(Vec2(_instance->centerWidth(), _instance->top(userLabel->getLineHeight())));
	}
	else {
		_instance->createSave();
	}
}

void Database::OnLoginRequestError(const PlayFab::PlayFabError& error, void* customData) {
	OnRequestError(error, customData);
	_instance->logout();
}

//Playfab callbacks - general

void Database::OnRequestError(const PlayFab::PlayFabError& error, void* customData) {
	_instance->_error = error.GenerateErrorReport();
	cocos2d::log(_instance->_error.c_str());
}

//Old requests

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

//GET requests

void Database::getUser() {
	PlayFab::ClientModels::LoginWithEmailAddressRequest request;
	request.Email = _email;
	request.Password = _password;
	request.InfoRequestParameters = new PlayFab::ClientModels::GetPlayerCombinedInfoRequestParams;
	request.InfoRequestParameters->GetPlayerProfile = true;
	request.InfoRequestParameters->ProfileConstraints = new PlayFab::ClientModels::PlayerProfileViewConstraints;
	request.InfoRequestParameters->ProfileConstraints->ShowDisplayName = true;

	PlayFab::PlayFabClientAPI::LoginWithEmailAddress(request, OnLoginRequestSuccess, OnLoginRequestError, nullptr);
}

bool Database::getCharacter() {
	std::string url = std::string("/items/characters?filter[user_id][_eq]=" + std::to_string(_user.id));

	if (request(url)) {
		_character = json::parse(_request.text)["data"][0].get<db::character>();

		//Getting character gears
		for (size_t i = 0; i < std::size(_character.gearsId); i++)
		{
			int id = _character.gearsId[i];

			if (id) {
				url = std::string("/items/gears/" + std::to_string(id));

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
	std::string url = std::string("/items/inventories?filter[user_id][_eq]=" + std::to_string(_user.id));

	if (request(url)) {
		_inventory = json::parse(_request.text)["data"][0].get<db::inventory>();

		//Getting inventory gears
		url = std::string("/items/gears?filter[inventory_id][_eq]=" + std::to_string(_inventory.id));

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

//POST requests

void Database::createUser() {
	_username = createUsername();

	PlayFab::ClientModels::RegisterPlayFabUserRequest request;
	request.Email = _email;
	request.Username = _username;
	request.DisplayName = _username;
	request.Password = _password;
	PlayFab::PlayFabClientAPI::RegisterPlayFabUser(request, OnRegisterRequestSuccess, OnRegisterRequestError, nullptr);
}

void Database::createCharacter() {
	/*std::string url = std::string(_url + "/items/characters");
	db::character character = { _user.id, 1 }; //Création de la struct

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
	}*/
}

bool Database::createInventory() {
	std::string url = std::string("/items/inventories");
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

void Database::createGear(db::gear gear) {
	gear.id = std::size(_gears) + 1;
	_gears.push_back(gear);
	updateGears();
}

void Database::createError() {
	cocos2d::log("creating error");
	std::string url = std::string("/items/errors");
	db::error error = { _request.status_code, _request.text, _user.id ? _user.id : 0 };
	json payload = error;
	request(url, payload);
}

void Database::update() {
	std::list<PlayFab::DataModels::SetObject> objects;
	objects.push_back(createUserObject());
	objects.push_back(createGearsObject());

	_setObjectsRequest.Objects = objects;

	PlayFab::PlayFabDataAPI::SetObjects(_setObjectsRequest, OnSetObjectsRequestSuccess, OnRequestError, nullptr);
}

void Database::updateUser() {
	std::list<PlayFab::DataModels::SetObject> objects;
	objects.push_back(createUserObject());

	_setObjectsRequest.Objects = objects;

	PlayFab::PlayFabDataAPI::SetObjects(_setObjectsRequest, OnSetObjectsRequestSuccess, OnRequestError, nullptr);
}

void Database::updateGears() {
	std::list<PlayFab::DataModels::SetObject> objects;
	objects.push_back(createGearsObject());

	_setObjectsRequest.Objects = objects;

	PlayFab::PlayFabDataAPI::SetObjects(_setObjectsRequest, OnSetObjectsRequestSuccess, OnRequestError, nullptr);
}

bool Database::updateCharacter() {
	std::string url = std::string("/items/characters/" + std::to_string(_character.id));
	json payload = _character;
	return patch(url, payload);
}

bool Database::updateInventory() {
	std::string url = std::string("/items/inventories/" + std::to_string(_inventory.id));
	json payload = _inventory;
	return patch(url, payload);
}

bool Database::updateGear(int index) {
	std::string url = std::string("/items/gears/" + std::to_string(_inventory.gears[index].id));
	json payload = _inventory.gears[index];
	return patch(url, payload);
}

bool Database::deleteUser() {
	std::string url = std::string("/items/users/" + std::to_string(_user.id));
	return deleteRequest(url);
}

bool Database::deleteGear(int index) {
	std::string url = std::string("/items/gears/" + std::to_string(_inventory.gears[index].id));
	_inventory.gears.erase(_inventory.gears.begin() + index);
	return deleteRequest(url);
}

void Database::setGear(db::gear gear) {
	_user.gears[gear.type] = gear.id;
	updateUser();
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

//PlayFab Objects

PlayFab::DataModels::SetObject Database::createUserObject() {
	json data = _hasSave ? _user : json({
		{"Energy", 50},
		{ "Cristals", 1000 },
		{ "Gender", 0 },
		{ "Tutorial", 1 },
		{ "Level", 1 },
		{ "Experience", 0 },
		{ "Gears", {0, 0, 0, 0, 0, 0, 0, 0} }
	});

	_user = data.get<db::user>();

	PlayFab::DataModels::SetObject object;
	object.ObjectName = "PlayerData";
	object.EscapedDataObject = data.dump();
	return object;
}

PlayFab::DataModels::SetObject Database::createGearsObject() {
	json data = _gears;

	PlayFab::DataModels::SetObject object;
	object.ObjectName = "PlayerGears";
	object.EscapedDataObject = data.dump();
	return object;
}

//Setters

void Database::setEmail(std::string email) { _email = email; }
void Database::emptyPull() { _lastPull.clear(); }

std::string Database::username() { return _username; }
db::user* Database::user() { return &_user; }
db::character* Database::character() { return &_character; }
db::inventory* Database::inventory() { return &_inventory; }
std::vector<db::gear>* Database::gears() { return &_gears; }
std::vector<db::support>* Database::lastPull() { return &_lastPull; }
bool Database::isLogged() { return _logged; }