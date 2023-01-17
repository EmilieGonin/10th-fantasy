#pragma once
#include <string>
#include <cpr/cpr.h>
#include "cocos2d.h"
#include <openssl/opensslv.h>

class Database
{
protected:
	std::string _url; //Testing only - to encrypt

public:
	Database();
	cpr::Response request(std::string);

	//GET requests
	void getUser();
};