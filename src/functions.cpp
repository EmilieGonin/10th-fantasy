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

//Lancée au démarrage de l'application pour setup le timer
void setTimer(int& energy, bool& ready) {
	std::cout << "Starting timer..." << std::endl;
	ready = true;
	int limit = 50; //La limite d'énergie en fonction du niveau du joueur (database)
	clock_t start, now, timePassed;

	while (energy < limit) { //Sera remplacé par while game is open
		if (energy < limit) {
			start = clock();
			timePassed = 0; //Le temps du timer précédent si on a pu le stocker à la fermeture du jeu
			int duration = 3000 - timePassed; //en ms, à remplacer par 300000 (5min)

			do {
				now = clock();

				//Données à stocker si on peut lancer une fonction lors de la fermeture du jeu
				timePassed = now - start;
			} while (timePassed < duration);

			energy++;
			std::cout << "energy : " << energy << std::endl;
			std::cout << "time passed : " << timePassed / 1000 << "s" << std::endl;
		}
	}
}