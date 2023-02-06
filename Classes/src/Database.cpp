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
	_url = "https://49g5s1t0.directus.app"; //To encrypt
}

bool Database::checkSave() {
	bool dataFound = false;
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
					dataFound = true;
				}
			}
		} while (std::getline(file, line));
	}

	file.close();
	return dataFound;
}

std::vector<std::string> Database::split(std::string string, std::string delim) {
	std::size_t delimIndex = string.find(delim);
	std::string setting = string.substr(0, delimIndex);
	std::string value = string.substr(delimIndex + 1);

	std::vector<std::string> data = { setting, value };
	return data;
}

bool Database::request(std::string url) {
	_request = cpr::Get(cpr::Url{ url }, cpr::VerifySsl{ false });
	return handleRequest(_request);
}

bool Database::request(std::string url, json payload) {
	_request = cpr::Post(
		cpr::Url{ url }, cpr::VerifySsl{ false },
		cpr::Body{ payload.dump() },
		cpr::Header{ {"Content-Type", "application/json"} });

	return handleRequest(_request);
}

bool Database::handleRequest(cpr::Response r) {
	cocos2d::log("**********"); //Help to see logs

	if (r.status_code == 0) { //Si la requête n'a pas pu être lancée
		cocos2d::log(r.error.message.c_str());
		return false;
	}
	else if (r.status_code >= 400) { //Si la requête a échoué
		std::string message = std::string("Error [" + std::to_string(r.status_code) + "] making request.");
		cocos2d::log(message.c_str());
		return false;
	}
	else { //On affiche le résultat dans la console (debug only)
		cocos2d::log(r.text.c_str());
		return true;
	}

	cocos2d::log("**********"); //Help to see logs
}

bool Database::getUser() {
	cocos2d::log("getting user");
	std::string url = std::string(_url + "/items/users?filter[mail][_eq]=" + _email);
	return request(url);
}

bool Database::createUser() {
	cocos2d::log("creating user");

	//Creating user
	std::ofstream file("user.txt");
	file << "User=" + _email << std::endl;
	file.close();

	std::string url = std::string(_url + "/items/users");
	db::user user = { std::string(_email) }; //Création de la struct
	json payload = user; //On convertis la struct en JSON
	return request(url, payload);
}

void Database::setEmail(std::string email) {
	_email = email;
}