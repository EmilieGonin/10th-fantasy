#include "PlayerManager.h"


PlayerManager* PlayerManager::_instance = new PlayerManager();

PlayerManager* PlayerManager::Instance() { return _instance; }

void PlayerManager::setPlayer(Player* myPlayer) { player = myPlayer; }
Player* PlayerManager::getPlayer(){ return player; }