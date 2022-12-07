#include "functions.h"

//Lanc�e au d�marrage de l'application pour setup le timer
void setTimer(int& energy) {
	clock_t start, now, timePassed;
	start = clock();
	timePassed = 0; //Le temps du timer pr�c�dent si on a pu le stocker � la fermeture du jeu
	int duration = 3000 - timePassed; //en ms, � remplacer par 300000 (5min)

	do {
		now = clock();

		//Donn�es � stocker si on peut lancer une fonction lors de la fermeture du jeu
		timePassed = now - start;
	} while (timePassed < duration);

	energy++;
	std::cout << "energy : " << energy << std::endl;
	std::cout << "time passed : " << timePassed << std::endl;
}