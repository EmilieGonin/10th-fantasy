#include "GameManager.h"


GameManager* GameManager::_instance = new GameManager();



GameManager* GameManager::Instance() {
	return _instance;
}