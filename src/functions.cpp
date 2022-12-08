#include "functions.h"

int rand(int range) {
	int random = rand() % range;
	return random;
}

void pull(int num) {
	for (size_t i = 0; i < num; i++)
	{
		int rarity = rand(1000);
		std::cout << "random : " << rarity << std::endl;

		if (rarity >= 0 && rarity < 5) {
			rarity = 3; //Legendary (0,5%)
		}
		else if (rarity >= 5 && rarity < 95) {
			rarity = 2; //Epic (9,5%)
		}
		else {
			rarity = 1; //Rare (90%)
		}

		//Vecteurs temporaires pour représenter la database
		//SELECT * FROM SUPPORTS WHERE RARITIES = (rarity)
		std::vector< std::vector<std::string>> database;
		std::vector<std::string> rare = { "first rare object","second rare object" ,"third rare object" ,"fourth rare object" ,"fifth rare object" };
		std::vector<std::string> epic = { "first epic object","second epic object" ,"third epic object" ,"fourth epic object" ,"fifth epic object" ,"sixth epic object" };
		std::vector<std::string> legendary = { "first legendary item", "second legendary item", "third legendary item" };
		database.push_back(rare); //0
		database.push_back(epic); //1
		database.push_back(legendary); //2

		int pull = rand(database[rarity - 1].size());
		std::cout << "Item pulled : " << database[rarity - 1][pull] << std::endl;
	}
}