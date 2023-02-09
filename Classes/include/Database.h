#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <optional>
#include <fstream>
#include "Interface.h"

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
	};

	struct character {
		int userId;
		int level;
		int id;
		int head;
		int chest;
		int gloves;
		int necklace;
		int earring;
		int ring;
		int weapon;
	};

	struct inventory {
		int userId;
		std::vector<int> weapons;
		std::vector<int> heads;
		std::vector<int> chests;
		std::vector<int> gloves;
		std::vector<int> necklaces;
		std::vector<int> earrings;
		std::vector<int> rings;
	};

	struct error {
		int code;
		std::string message;
		int userId;
	};

	//JSON -> STRUCT
	void from_json(const json& j, user& user);
	void from_json(const json& j, character& character);
	void from_json(const json& j, inventory& inventory);
	//STRUCT -> JSON
	void to_json(json& j, const user& user);
	void to_json(json& j, const character& character);
	void to_json(json& j, const inventory& inventory);
	void to_json(json& j, const error& error);
}

class Database : Interface
{
private:
	Database();
	static Database* _instance;
	cocos2d::Scene* _scene;
	db::user _user;
	db::character _character;
	db::inventory _inventory;
	std::string _url; //Testing only - to encrypt
	cpr::Response _request;
	std::string _email;
	int _userId;

public:
	static Database* Instance();

	//Wrapper pour créer les requêtes et gérer les erreurs
	//Peut être utilisé pour les requêtes GET et POST avec une surcharge
	bool request(std::string); //GET
	bool request(std::string, json); //POST
	bool handleRequest(cpr::Response);
	std::vector<std::string> split(std::string, std::string);

	//Pour vérifier les données au lancement du jeu
	void init(cocos2d::Scene*);
	bool checkSave();
	void createSave();
	void signup();
	void login();

	//GET requests
	bool getUser();

	//POST requests
	bool createUser();
	void createError();

	//UPDATE requests
	bool update(db::user);
	bool update(db::character);
	bool update(db::inventory);

	//Setters
	void setEmail(std::string);

	//Getters
	db::user getUserData();
	db::character getCharacterData();
	db::inventory getInventoryData();
};