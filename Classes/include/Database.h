#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <optional>
#include <fstream>
#include "Interface.h"
#include "GameManager.h"

#include "PlayFabClientAPI.h"
#include "PlayFabDataAPI.h"
#include "PlayFabAuthenticationAPI.h"
#include <PlayFabSettings.h>

using json = nlohmann::json; //On raccourcis le namespace
using namespace cocos2d::ui;

namespace db { //Les structures et fonctions utilisées pour le JSON
	struct user {
		int energy;
		int cristals;
		int gender; //1 = Male, 2 = Female
		int tutorial;
		int level;
		int exp;
		std::vector<int> gears;
		int id;
		std::vector<int> supports;
	};

	struct stat {
		int statId;
		int rate;
		int percentage;
	};

	struct support {
		int supportId;
		std::string name;
		int rarity;
		int type;
		std::vector<stat> stats;
		int convertAmount;
	};

	struct gear {
		int type;
		int stat;
		int amount;
		int rarity;
		int level;
		int id;
	};

	struct character {
		int userId;
		int level;
		int exp;
		int gearsId[8];
		int supportsId[2];
		db::gear gears[8];
		db::support supports[2];
		int id;
	};

	struct inventory {
		int userId;
		std::vector<gear> gears;
		int id;
	};

	struct error {
		int code;
		std::string message;
		int userId;
	};

	//JSON -> STRUCT
	void from_json(const json& j, user& user);
	void from_json(const json& j, character& character);
	void from_json(const json& j, stat& stat);
	void from_json(const json& j, support& support);
	void from_json(const json& j, inventory& inventory);
	void from_json(const json& j, gear& gear);
	//STRUCT -> JSON
	void to_json(json& j, const user& user);
	void to_json(json& j, const character& character);
	void to_json(json& j, const inventory& inventory);
	void to_json(json& j, const gear& gear);
	void to_json(json& j, const error& error);
}

class Database : Interface
{
private:
	Database();
	static Database* _instance;
	cocos2d::Scene* _scene;
	GameManager* _gameManager;

	//Database datas
	db::user _user;
	db::character _character;
	db::inventory _inventory;
	std::vector<db::gear> _gears;

	cpr::Response _request;
	bool _logged;
	std::vector<db::support> _lastPull;

	//PlayFab
	std::string _id; //To encrypt
	std::string _error;
	std::string _email;
	std::string _username;
	std::string _password;
	PlayFab::DataModels::SetObjectsRequest _setObjectsRequest;
	PlayFab::DataModels::GetObjectsRequest _getObjectsRequest;
	PlayFab::ClientModels::EntityTokenResponse* _token;

	bool _hasSave;

public:
	static Database* Instance();

	//Wrapper pour créer les requêtes et gérer les erreurs
	//Peut être utilisé pour les requêtes GET et POST avec une surcharge
	bool request(std::string); //GET
	bool request(std::string, json); //POST
	bool patch(std::string, json); //PATCH
	bool deleteRequest(std::string); //DELETE
	bool handleRequest();

	//Wrappers
	std::vector<std::string> split(std::string, std::string);
	std::string createUsername();
	void setEntityKey(PlayFab::ClientModels::EntityTokenResponse*);

	//Pour vérifier les données au lancement du jeu
	void init(cocos2d::Scene*);
	bool checkSave();
	void createSave();
	void deleteSave();
	void signup();
	void login();
	void logout();

	//PlayFab callbacks - register
	static void OnRegisterRequestSuccess(const PlayFab::ClientModels::RegisterPlayFabUserResult&, void*);
	static void OnSetObjectsRequestSuccess(const PlayFab::DataModels::SetObjectsResponse&, void*);
	static void OnRegisterRequestError(const PlayFab::PlayFabError&, void*);

	//PlayFab callbacks - login
	static void OnLoginRequestSuccess(const PlayFab::ClientModels::LoginResult&, void*);
	static void OnGetObjectsRequestSuccess(const PlayFab::DataModels::GetObjectsResponse&, void*);
	static void OnLoginRequestError(const PlayFab::PlayFabError&, void*);

	//PlayFab callbacks - general
	static void OnRequestError(const PlayFab::PlayFabError&, void*);

	//GET requests
	void getUser();
	bool getCharacter();
	bool getInventory();

	//POST requests
	void createUser();
	void createCharacter();
	bool createInventory();
	void createGear(db::gear);
	void createError();

	//UPDATE requests
	void update();
	void updateUser();
	bool updateCharacter();
	bool updateInventory();
	bool updateGear(int);
	void updateGears();

	//DELETE requests
	bool deleteUser();
	bool deleteGear(int);

	//Setters
	void setGear(db::gear);
	void setSupport(db::support, int);

	//Local Json
	std::vector<db::support> getSupports(int);
	db::support getSupport(int);

	//PlayFab Objects
	PlayFab::DataModels::SetObject createUserObject();
	PlayFab::DataModels::SetObject createGearsObject();

	//Setters
	void setEmail(std::string);
	void emptyPull();

	//Getters
	std::string username();
	db::user* user();
	db::character* character();
	db::inventory* inventory();
	std::vector<db::support>* lastPull();
	bool isLogged();
};