#pragma once
#include <string>
#include <cpr/cpr.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include "Interface.h"

using json = nlohmann::json; //On raccourcis le namespace
using namespace cocos2d::ui;

class Database : Interface
{
private:
	Database();
	static Database* _instance;
	cocos2d::Scene* _scene;
	json _user;
	json _character;
	json _inventory;
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
	void setEmail(std::string);
};