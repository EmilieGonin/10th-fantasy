
#include <iostream>
#include <vector>
#include <thread>

#include "Enemy.h"
#include "Player.h"
#include "Battle.h"
#include "Entity.h"
#include "functions.h" //Temporary functions outside classes

Enemy enemy;
Enemy enemy2;
Enemy enemy3;
Enemy enemy4;
Player player;


int main()
{
    std::vector<Enemy*> myVector;
    myVector.push_back(&enemy);
    myVector.push_back(&enemy2);
    myVector.push_back(&enemy3);
    myVector.push_back(&enemy4);

    Battle battle(&player, myVector);
    
    int energy = 30; //Le taux d'énergie actuellement possédé par le joueur (database)
    bool ready = false;
    std::thread timer(setTimer, std::ref(energy), std::ref(ready));
    timer.detach();

    while (!ready) {}; //Waiting for timer to start

    srand(time(0)); //Initialize rand seed once
    std::cout << "Pulling 1 item..." << std::endl;
    pull(1);
    std::cout << std::endl;
    std::cout << "Pulling 10 items..." << std::endl;
    pull(10);

    while (battle.getBattleState()) {
        battle.turn();
        battle.battleCheck();
    }

    std::cout << "battle end";

    return 0;
}

