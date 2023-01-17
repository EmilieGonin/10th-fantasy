#include "Database.h"

using json = nlohmann::json; //On raccourcis le namespace
namespace db { //Les structures et fonctions utilisées pour le JSON
	struct user {
		std::string mail;
	};

	void to_json(json& j, const user& user) { //Fonction appelée pour convertir
		j = json{ {"mail", user.mail } };
	}
}

Database::Database() {
	_url = "https://49g5s1t0.directus.app";
	createUser();
}

cpr::Response Database::request(std::string url) {
	cpr::Response r = cpr::Get(cpr::Url{ url }, cpr::VerifySsl{ false });
	handleRequest(r);
	return r;
}

cpr::Response Database::request(std::string url, json payload) {
	cpr::Response r = cpr::Post(
		cpr::Url{ url }, cpr::VerifySsl{ false },
		cpr::Body{ payload.dump() },
		cpr::Header{ {"Content-Type", "application/json"} });
	handleRequest(r);
	return r;
}

void Database::handleRequest(cpr::Response r) {
	cocos2d::log("**********"); //Help to see logs

	if (r.status_code == 0) { //Si la requête n'a pas pu être lancée
		cocos2d::log(r.error.message.c_str());
	}
	else if (r.status_code >= 400) { //Si la requête a échoué
		std::string message = std::string("Error [" + std::to_string(r.status_code) + "] making request.");
		cocos2d::log(message.c_str());
	}
	else { //On affiche le résultat dans la console (debug only)
		cocos2d::log(r.text.c_str());
	}

	cocos2d::log("**********"); //Help to see logs
}

void Database::getUser() {
	std::string url = std::string(_url + "/items/users");
	cpr::Response r = request(url);
}

void Database::createUser() {
	std::string url = std::string(_url + "/items/users");
	db::user user = { std::string("test@test.com") }; //Création de la struct
	json payload = user; //On convertis la struct en JSON
	cpr::Response r = request(url, payload);
}