#pragma once
#include <string>
#include <cpr/cpr.h>
#include "cocos2d.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

class Database
{
protected:
	std::string _url; //Testing only - to encrypt
	cpr::Response _request;
	std::string _email;

public:
	Database();

	//Wrapper pour cr�er les requ�tes et g�rer les erreurs
	//Peut �tre utilis� pour les requ�tes GET et POST avec une surcharge
	bool request(std::string); //GET
	bool request(std::string, nlohmann::json); //POST
	bool handleRequest(cpr::Response);
	std::vector<std::string> split(std::string, std::string);
	bool checkSave();


	//GET requests
	bool getUser();

	//POST requests
	bool createUser();
	void setEmail(std::string);
};