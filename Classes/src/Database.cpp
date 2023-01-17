#include "Database.h"

Database::Database() {
	_url = "https://49g5s1t0.directus.app";
}

cpr::Response Database::request(std::string url) {
	cpr::Response r = cpr::Get(cpr::Url{ url }, cpr::VerifySsl{ false });
	cocos2d::log("**********"); //Help to see logs

	if (r.status_code == 0) {
		cocos2d::log(r.error.message.c_str());
	}
	else if (r.status_code >= 400) {
		std::string message = std::string("Error [" + std::to_string(r.status_code) + "] making request.");
		cocos2d::log(message.c_str());
	}
	else {
		cocos2d::log(r.text.c_str());
	}

	cocos2d::log("**********"); //Help to see logs
	return r;
}

void Database::getUser() {
	std::string url = std::string(_url + "/items/users");
	cpr::Response r = request(url);
}