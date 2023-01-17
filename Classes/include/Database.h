#pragma once
#include <string>
#include <cpr/cpr.h>
#include "cocos2d.h"
#include <nlohmann/json.hpp>

class Database
{
protected:
	std::string _url; //Testing only - to encrypt

public:
	Database();

	//Wrapper pour créer les requêtes et gérer les erreurs
	//Peut être utilisé pour les requêtes GET et POST avec une surcharge
	cpr::Response request(std::string); //GET
	cpr::Response request(std::string, nlohmann::json); //POST
	void handleRequest(cpr::Response);

	//GET requests
	void getUser();

	//POST requests
	void createUser();
};