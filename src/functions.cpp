#include "functions.h"

//Lancée au démarrage de l'application pour setup le timer
void setTimer(int& energy) {
	clock_t start, now, timePassed;
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
	std::cout << "time passed : " << timePassed << std::endl;
}