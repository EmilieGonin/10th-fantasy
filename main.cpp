// Lors de l'ajout d'un fichier .h, modifier l'emplacement du fichier vers le dossier "include"
// Lors de l'ajout d'un fichier .cpp, modifier l'emplacement du fichier vers le dossier "src

#include <iostream>
#include "functions.h" //Temporary functions outside classes

int main()
{
    int minutes = 60; //Le nombre de minutes pass� sur le jeu
	int energy = 30; //Le taux d'�nergie actuellement poss�d� par le joueur (database)
	int limit = 50; //La limite d'�nergie en fonction du niveau du joueur (database)

	while (energy < limit) { //Sera remplac� while game is open
		if (energy < limit) {
			setTimer(energy);
		}
		minutes - 5; //Temp
	}
}