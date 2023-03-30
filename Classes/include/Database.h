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

using json = nlohmann::json; //On raccourcis le namespace
using namespace cocos2d::ui;

namespace db { //Les structures et fonctions utilisées pour le JSON
	struct user {
		std::string mail;
		std::string name;
		int level;
		int energy;
		int cristals;
		int leafs;
		int wishes;
		int tickets;
		int timer;
		int id;
		std::vector<int> supports;
	};

	struct character {
		int userId;
		int level;
		int head;
		int chest;
		int gloves;
		int necklace;
		int earring;
		int ring;
		int weapon;
		int id;
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
	};

	struct gear {
		int inventoryId;
		int type;
		int stat;
		int amount;
		int rarity;
		int level;
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
	db::user _user;
	db::character _character;
	db::inventory _inventory;
	std::string _url; //Testing only - to encrypt
	cpr::Response _request;
	std::string _email;

public:
	static Database* Instance();

	//Wrapper pour créer les requêtes et gérer les erreurs
	//Peut être utilisé pour les requêtes GET et POST avec une surcharge
	bool request(std::string); //GET
	bool request(std::string, json); //POST
	bool patch(std::string, json); //PATCH
	bool deleteRequest(std::string); //DELETE
	bool handleRequest();
	std::vector<std::string> split(std::string, std::string);

	//Pour vérifier les données au lancement du jeu
	void init(cocos2d::Scene*);
	bool checkSave();
	void createSave();
	void deleteSave();
	void signup();
	void login();

	//GET requests
	bool getUser();
	bool getCharacter();
	bool getInventory();

	//POST requests
	bool createUser();
	bool createCharacter();
	bool createInventory();
	bool createGear(db::gear);
	void createError();

	//UPDATE requests
	bool update();
	bool updateUser();
	bool updateCharacter();
	bool updateInventory();
	bool updateGear(int);

	//DELETE requests
	bool deleteUser();
	bool deleteGear(int);

	//Local Json
	std::vector<db::support> getSupports(int);
	db::support getSupport(int);

	//Setters
	void setEmail(std::string);

	//Getters
	db::user* user();
	db::character* character();
	db::inventory* inventory();
};