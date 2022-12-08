// Lors de l'ajout d'un fichier .h, modifier l'emplacement du fichier vers le dossier "include"
// Lors de l'ajout d'un fichier .cpp, modifier l'emplacement du fichier vers le dossier "src

#include <iostream>
#include "functions.h" //Temporary functions outside classes

int main()
{
    srand(time(0)); //Initialize rand seed once
    std::cout << "Pulling 1 item..." << std::endl;
    pull(1);
    std::cout << std::endl;
    std::cout << "Pulling 10 items..." << std::endl;
    pull(10);
    
    int minutes = 60; //Le nombre de minutes passé sur le jeu
    int energy = 30; //Le taux d'énergie actuellement possédé par le joueur (database)
  	int limit = 50; //La limite d'énergie en fonction du niveau du joueur (database)
    
    while (energy < limit) { //Sera remplacé par while game is open
        if (energy < limit) {
            setTimer(energy);
        }
        minutes - 5; //Temp
    }
}