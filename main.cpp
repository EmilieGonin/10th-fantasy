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
}