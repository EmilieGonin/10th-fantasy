
#include <iostream>
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "Battle.h"
#include "Entity.h"

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

    while (battle.getBattleState()) {
        battle.turn();
        battle.battleCheck();
    }

    std::cout << "battle end";

}
