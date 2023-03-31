#include "Battle.h"
#include "MainMenuScene.h"

#include <iostream>

Battle::Battle(Player* player, std::vector<Enemy*> enemies, int _bossCheck) {
	_player = player;
	_enemies = enemies;
	_battle = true;

	selectedSkill = -1;
	selectedEnemy = -1;
	iPlay = 1;

	gameManager = GameManager::Instance();
	database = Database::Instance();

	myLifeBar = cocos2d::DrawNode::create();
	enemyLifeBar = cocos2d::DrawNode::create();

	/*rectangle[0] = cocos2d::Vec2(0, -8);
	rectangle[1] = cocos2d::Vec2(100, -8);
	rectangle[2] = cocos2d::Vec2(100 , 5);
	rectangle[3] = cocos2d::Vec2(0, 5);

	rectangle2[0] = cocos2d::Vec2(0, -15);
	rectangle2[1] = cocos2d::Vec2(300, -15);
	rectangle2[2] = cocos2d::Vec2(300, 15);
	rectangle2[3] = cocos2d::Vec2(0, 15);*/

	myLifeBar->drawSolidRect(cocos2d::Vec2(0, 0), cocos2d::Vec2(100, 20), cocos2d::Color4F::GREEN);
	myLifeBar->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	myLifeBar->setPosition(cocos2d::Vec2(30, 500));

	enemyLifeBar->drawSolidRect(cocos2d::Vec2(0, 0), cocos2d::Vec2(250, 20), cocos2d::Color4F::GREEN);
	enemyLifeBar->setAnchorPoint(cocos2d::Vec2(0.0, 0.0));
	enemyLifeBar->setPosition(cocos2d::Vec2(200, 720));

	_player->update();
	//myLifeBar->drawPolygon(rectangle, 4, cocos2d::Color4F::GREEN, 1, cocos2d::Color4F::GREEN);
	//enemyLifeBar->drawPolygon(rectangle2, 4, cocos2d::Color4F::GREEN, 1, cocos2d::Color4F::GREEN);

	//Support Time 
	cocos2d::log(_player->getSupport()[0]->getSupportStat()->name.c_str());
	for (int index = 0; index < _player->getSupport().size(); index++)
	{

		if (_player->getSupport()[index]->getSupportStat()->type == 2)
		{
			std::vector<db::stat> effect = _player->getSupport()[index]->getSupportStat()->stats;
			for (int statIndex = 0; statIndex < effect.size(); statIndex++)
			{
				if (effect[statIndex].percentage == 0)
				{
					CCLOG("going up");
					CCLOG("%d", effect[statIndex].statId);
					CCLOG("%d", *_player->getTotalStats()[effect[statIndex].statId]);
					*_player->getTotalStats()[effect[statIndex].statId] += effect[statIndex].rate;
					CCLOG("%d", *_player->getTotalStats()[effect[statIndex].statId]);
				}
				else if (effect[statIndex].percentage == 1)
				{
					CCLOG("going upppppp");
					float rate = (effect[statIndex].rate / 100.0000);
					float amount = *_player->getTotalStats()[effect[statIndex].statId] * rate;
					CCLOG("%f", rate);
					CCLOG("%d", _player->getBattleHP());
					*_player->getTotalStats()[effect[statIndex].statId] += (int)amount;
					CCLOG("%d", *_player->getTotalStats()[effect[statIndex].statId]);
				}
			}
		}
	}

	for (int i = 0; i < _enemies.size(); i++) {
		_battleOrder.push_back(_enemies[i]);
	}

	_battleOrder.push_back(_player);
	play();
}

Battle::~Battle() {};

void Battle::attack(Entity* attacker, Entity* target, Skill* skillUsed) {
	int usedDef;
	float multiplicatorType;

	if (attacker->getDamageType() == 0) {
		usedDef = *target->getTotalStats()[PDEF];
		multiplicatorType = 1 + ((float)*attacker->getTotalStats()[PATK] / 100.0000);
		std::cout << "Physical damage" << std::endl;
	}
	else {
		usedDef = *target->getTotalStats()[MDEF];
		multiplicatorType = 1 + (*attacker->getTotalStats()[MATK] / 100.0000);
	}
	float atk = (float)*attacker->getTotalStats()[ATK];
	float def = (float)usedDef;
	float damage = ((atk * multiplicatorType) * (1000 / (1000 + def))) * skillUsed->getMultiplier();

	if (damage <= 0) {
		damage = 0;
	}
	int cr = rand() % 100;
	if (cr < *attacker->getTotalStats()[CR]) {
		damage = damage * *attacker->getTotalStats()[CD];
	}

	CCLOG("Mdama fzerg LIER %f", damage);
	target->looseHp(damage);
	myDamage = newLabel(std::to_string(damage));
	myDamage->setPosition(Vec2(target->getSprite()->getPosition().x, target->getSprite()->getPosition().y + 200));

	//addChild(mydamagetext);
	skillUsed->_cooldown = skillUsed->_maxCooldown;

	selectedSkill = -1;
	//skillUsed.additionalEffect(attacker, target, damage);
}

void Battle::play() {
	for (int i = 0; i < _battleOrder.size(); i++) {
		if (iPlay == i)
		{
			_myTurn = true;
		}
		if (_myTurn != true)
		{
			int num = rand() % 1;
			CCLOG("Enemy attacks");
			attack(_battleOrder[i], _player, _battleOrder[i]->getSkills()[num]);
			for (int a = 0; a < _battleOrder[i]->getSkills().size(); a++)
			{
				if (_battleOrder[i]->getSkills()[a]->_maxCooldown == 0 || _battleOrder[i]->getSkills()[a]->_cooldown > 0)
				{
					_battleOrder[i]->getSkills()[a]->_cooldown -= 1;
				}
			}
			if (_player->getBattleHP() == 0)
			{
				_battle = false;
				cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
			}
		}
		else
		{

			if (selectedEnemy > -1 && selectedSkill > -1)
			{
				CCLOG("I attack");

				attack(_player, _enemies[selectedEnemy], _player->getSkills()[selectedSkill]);

				for (int a = 0; a < _player->getSkills().size(); a++)
				{
					if (_player->getSkills()[a]->_cooldown > 0)
					{
						_player->getSkills()[a]->_cooldown -= 1;
					}
				}
				selectedEnemy = selectedSkill = -1;
				_myTurn = false;
				battleCheck();
				play();


			}
		}
	}
	updateLifeBar();
}

void Battle::battleCheck() {
	CCLOG("Checking ");
	for (int i = 0; i < _battleOrder.size(); i++) {
		if (_battleOrder[i]->getBattleHP() <= 0) {
			CCLOG("I delete");
			_battleOrder.erase(_battleOrder.begin() + i);
		}
	}
	if (_battleOrder.size() == 1 && _player->getBattleHP() > 0) {
		CCLOG("I WIN");
		drop();
		_battle = false;
		_win = true;
		cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
	}
}

void Battle::drop() {
	int rarities[4];
	for (int i = 0; i < 4; i++) {
		rarities[i] = gameManager->getBoss()->getRarities()[i];
	}

	CCLOG("inventory size %d", database->inventory()->gears.size());
	switch (gameManager->getBossId())
	{
		int rd;
	case 1:
		break;
	case 2:
		rd = rand() % 3;
		switch (rd)
		{
		case 0:
			CCLOG("je drop");
			database->createGear(createNecklace(rarities));
			break;
		case 1:
			CCLOG("je drop");
			database->createGear(createRing(rarities));
			break;
		case 2:
			CCLOG("je drop");
			database->createGear(createEarRing(rarities));
			break;
		}
		break;
	case 3:
		rd = rand() % 3;
		switch (rd)
		{
		case 0:
			CCLOG("je drop");
			database->createGear(createHelmet(rarities));
			break;
		case 1:
			CCLOG("je drop");
			database->createGear(createChest(rarities));
			break;
		case 2:
			CCLOG("je drop");
			database->createGear(createBoots(rarities));
			break;
		}
		break;
	}
	CCLOG("inventory size %d", database->inventory()->gears.size());
}

bool Battle::getBattleState() { return _battle; }
bool Battle::getMyTurn() { return _myTurn; }
int Battle::getSelected() { return selectedSkill; }
cocos2d::DrawNode* Battle::getLifeBar() { return myLifeBar; }
cocos2d::DrawNode* Battle::getEnemyLifeBar() { return enemyLifeBar; }

void Battle::updateLifeBar()
{
	myLifeBar->clear();
	myLifeBar->drawSolidRect(cocos2d::Vec2(0, 0), cocos2d::Vec2(100 * _player->getBattleHP() / *_player->getTotalStats()[HP], 20), cocos2d::Color4F::RED);

	enemyLifeBar->clear();
	CCLOG("%d", _enemies[0]->getBattleHP());
	enemyLifeBar->drawSolidRect(cocos2d::Vec2(0, 0), cocos2d::Vec2(300 * _enemies[0]->getBattleHP() / *_enemies[0]->getTotalStats()[HP], 20), cocos2d::Color4F::RED);

	//rectangle[0] = cocos2d::Vec2(0, -8);
	//rectangle[1] = cocos2d::Vec2(100 * _player->getBattleHP() / *_player->getTotalStats()[HP], -8);
	//rectangle[2] = cocos2d::Vec2(100 * _player->getBattleHP() / *_player->getTotalStats()[HP], 5);
	//rectangle[3] = cocos2d::Vec2(0, 5);
	//myLifeBar->drawPolygon(rectangle, 4, cocos2d::Color4F::GREEN, 1, cocos2d::Color4F::GREEN);
	//enemyLifeBar->drawPolygon(rectangle2, 4, cocos2d::Color4F::GREEN, 1, cocos2d::Color4F::GREEN);
}

void Battle::setSelected(int selected)
{
	selectedSkill = selected;
}
void Battle::selectEnemy(int selected)
{
	selectedEnemy = selected;
	play();

}

db::gear Battle::createNecklace(int* rarity) {

	db::gear Necklace;
	Necklace.type = gameManager->NECKLACE;
	int rd = rand() % 4;
	switch (rd)
	{
	case 0:
		Necklace.stat = gameManager->MATK;
		break;
	case 1:
		Necklace.stat = gameManager->PATK;
		break;
	case 2:
		Necklace.stat = gameManager->CR;
		break;
	case 3:
		Necklace.stat = gameManager->CD;
		break;
	}

	int rd2 = rand() % 100;
	if (rd2 < rarity[0]) {
		switch (Necklace.stat)
		{
		case 1:
		{
			int M = rand() % 5 + 3;
			Necklace.amount = M;
			break;
		}
		case 2:
		{
			int Ph = rand() % 5 + 3;
			Necklace.amount = Ph;
			break;

		}
		case 6:
		{
			int CR = rand() % 5 + 1;
			Necklace.amount = CR;
			break;
		}
		case 7:
		{
			int CD = rand() % 10 + 5;
			Necklace.amount = CD;
			break;
		}
		}

		Necklace.rarity = gameManager->COMMON;
	}
	else if (rd2 > rarity[0] && rd2 < (rarity[0] + rarity[1]))
	{
		switch (Necklace.stat)
		{
		case 1:
		{
			int M = rand() % 8 + 6;
			Necklace.amount = M;
			break;
		}
		case 2:
		{
			int Ph = rand() % 8 + 6;
			Necklace.amount = Ph;
			break;
		}
		case 6:
		{
			int CR = rand() % 11 + 6;
			Necklace.amount = CR;
			break;
		}
		case 7:
		{
			int CD = rand() % 20 + 11;
			Necklace.amount = CD;
			break;
		}
		}

		Necklace.rarity = gameManager->RARE;
	}
	else if (rd2 > (rarity[0] + rarity[1]) && rd2 < (rarity[0] + rarity[1] + rarity[2]))
	{
		switch (Necklace.stat)
		{
		case 1:
		{
			int M = rand() % 12 + 9;
			Necklace.amount = M;
			break;
		}
		case 2:
		{
			int Ph = rand() % 12 + 9;
			Necklace.amount = Ph;
			break;
		}
		case 6:
		{
			int CR = rand() % 17 + 12;
			Necklace.amount = CR;
			break;
		}
		case 7:
		{
			int CD = rand() % 33 + 21;
			Necklace.amount = CD;
			break;
		}
		}

		Necklace.rarity = gameManager->EPIC;
	}
	else if (rd2 > (rarity[0] + rarity[1] + rarity[2]) && rd2 < (rarity[0] + rarity[1] + rarity[2] + rarity[3]))
	{
		switch (Necklace.stat)
		{
		case 1:
		{
			int M = rand() % 17 + 13;
			Necklace.amount = M;
			break;
		}
		case 2:
		{
			int Ph = rand() % 17 + 13;
			Necklace.amount = Ph;
			break;
		}
		case 6:
		{
			int CR = rand() % 24 + 18;
			Necklace.amount = CR;
			break;
		}
		case 7:
		{
			int CD = rand() % 50 + 34;
			Necklace.amount = CD;
			break;
		}
		}
		Necklace.rarity = gameManager->LEGENDARY;
	}

	Necklace.level = 0;
	return Necklace;
}

db::gear Battle::createEarRing(int* rarity) {

	db::gear EarRing;
	EarRing.type = gameManager->EARRING;
	int rd = rand() % 2;
	switch (rd)
	{
	case 0:
		EarRing.stat = gameManager->CR;
		break;
	case 1:
		EarRing.stat = gameManager->CD;
		break;
	}

	int rd2 = rand() % 100;
	if (rd2 < rarity[0]) {
		switch (EarRing.stat)
		{
		case 6:
		{
			int CR = rand() % 10 + 5;
			EarRing.amount = CR;
			break;
		}
		case 7:
		{
			int CD = rand() % 20 + 10;
			EarRing.amount = CD;
			break;
		}
		}

		EarRing.rarity = gameManager->COMMON;
	}
	else if (rd2 > rarity[0] && rd2 < (rarity[0] + rarity[1]))
	{
		switch (EarRing.stat)
		{
		case 6:
		{
			int CR = rand() % 16 + 11;
			EarRing.amount = CR;
			break;
		}
		case 7:
		{
			int CD = rand() % 33 + 21;
			EarRing.amount = CD;
			break;
		}
		}

		EarRing.rarity = gameManager->RARE;
	}
	else if (rd2 > (rarity[0] + rarity[1]) && rd2 < (rarity[0] + rarity[1] + rarity[2]))
	{
		switch (EarRing.stat)
		{
		case 6:
		{
			int CR = rand() % 27 + 18;
			EarRing.amount = CR;
			break;
		}
		case 7:
		{
			int CD = rand() % 49 + 34;
			EarRing.amount = CD;
			break;
		}
		}

		EarRing.rarity = gameManager->EPIC;
	}
	else if (rd2 > (rarity[0] + rarity[1] + rarity[2]) && rd2 < (rarity[0] + rarity[1] + rarity[2] + rarity[3]))
	{
		switch (EarRing.stat)
		{
		case 6:
		{
			int CR = rand() % 33 + 23;
			EarRing.amount = CR;
			break;
		}
		case 7:
		{
			int CD = rand() % 70 + 50;
			EarRing.amount = CD;
			break;
		}
		}
		EarRing.rarity = gameManager->LEGENDARY;
	}

	EarRing.level = 0;
	return EarRing;

}

db::gear Battle::createRing(int* rarity) {

	db::gear Ring;
	Ring.type = gameManager->RING;
	int rd = rand() % 2;
	switch (rd)
	{
	case 0:
		Ring.stat = gameManager->MATK;
		break;
	case 1:
		Ring.stat = gameManager->PATK;
		break;
	}

	int rd2 = rand() % 100;
	if (rd2 < rarity[0]) {
		switch (Ring.stat)
		{
		case 1:
		{
			int M = rand() % 10 + 5;
			Ring.amount = M;
			break;
		}
		case 2:
		{
			int Ph = rand() % 10 + 5;
			Ring.amount = Ph;
			break;
		}
		}

		Ring.rarity = gameManager->COMMON;
	}
	else if (rd2 > rarity[0] && rd2 < (rarity[0] + rarity[1]))
	{
		switch (Ring.stat)
		{
		case 1:
		{
			int M = rand() % 17 + 11;
			Ring.amount = M;
			break;
		}
		case 2:
		{
			int Ph = rand() % 17 + 11;
			Ring.amount = Ph;
			break;
		}
		}

		Ring.rarity = gameManager->RARE;
	}
	else if (rd2 > (rarity[0] + rarity[1]) && rd2 < (rarity[0] + rarity[1] + rarity[2]))
	{
		switch (Ring.stat)
		{
		case 1:
		{
			int M = rand() % 25 + 18;
			Ring.amount = M;
			break;
		}
		case 2:
		{
			int Ph = rand() % 25 + 18;
			Ring.amount = Ph;
			break;
		}
		}

		Ring.rarity = gameManager->EPIC;
	}
	else if (rd2 > (rarity[0] + rarity[1] + rarity[2]) && rd2 < (rarity[0] + rarity[1] + rarity[2] + rarity[3]))
	{
		switch (Ring.stat)
		{
		case 1:
		{
			int M = rand() % 35 + 26;
			Ring.amount = M;
			break;
		}
		case 2:
		{
			int Ph = rand() % 35 + 26;
			Ring.amount = Ph;
			break;
		}
		}
		Ring.rarity = gameManager->LEGENDARY;
	}

	Ring.level = 0;
	return Ring;

}

db::gear Battle::createHelmet(int* rarity) {

	db::gear Helmet;
	Helmet.type = gameManager->HELMET;
	Helmet.stat = gameManager->HP;

	int rd2 = rand() % 100;
	if (rd2 < rarity[0]) {
		int Hp = rand() % 1500 + 800;
		Helmet.amount = Hp;
		Helmet.rarity = gameManager->COMMON;
	}
	else if (rd2 > rarity[0] && rd2 < (rarity[0] + rarity[1]))
	{
		int Hp = rand() % 2800 + 1800;
		Helmet.amount = Hp;
		Helmet.rarity = gameManager->RARE;
	}
	else if (rd2 > (rarity[0] + rarity[1]) && rd2 < (rarity[0] + rarity[1] + rarity[2]))
	{
		int Hp = rand() % 5500 + 3000;
		Helmet.amount = Hp;
		Helmet.rarity = gameManager->EPIC;
	}
	else if (rd2 > (rarity[0] + rarity[1] + rarity[2]) && rd2 < (rarity[0] + rarity[1] + rarity[2] + rarity[3]))
	{
		int Hp = rand() % 8000 + 6000;
		Helmet.amount = Hp;
		Helmet.rarity = gameManager->LEGENDARY;
	}

	Helmet.level = 0;
	return Helmet;

}

db::gear Battle::createChest(int* rarity) {

	db::gear Chest;
	Chest.type = gameManager->CHEST;
	int rd = rand() % 2;
	switch (rd)
	{
	case 0:
		Chest.stat = gameManager->PDEF;
		break;
	case 1:
		Chest.stat = gameManager->MDEF;
		break;
	}

	int rd2 = rand() % 100;
	if (rd2 < rarity[0]) {

		int Def = rand() % 80 + 50;
		Chest.amount = Def;
		Chest.rarity = gameManager->COMMON;
	}
	else if (rd2 > rarity[0] && rd2 < (rarity[0] + rarity[1]))
	{
		int Def = rand() % 170 + 100;
		Chest.amount = Def;
		Chest.rarity = gameManager->RARE;
	}
	else if (rd2 > (rarity[0] + rarity[1]) && rd2 < (rarity[0] + rarity[1] + rarity[2]))
	{
		int Def = rand() % 290 + 200;
		Chest.amount = Def;
		Chest.rarity = gameManager->EPIC;
	}
	else if (rd2 > (rarity[0] + rarity[1] + rarity[2]) && rd2 < (rarity[0] + rarity[1] + rarity[2] + rarity[3]))
	{
		int Def = rand() % 500 + 330;
		Chest.amount = Def;
		Chest.rarity = gameManager->LEGENDARY;
	}

	Chest.level = 0;
	return Chest;
}

db::gear Battle::createBoots(int* rarity) {

	db::gear Boots;
	Boots.type = gameManager->BOOT;
	Boots.stat = gameManager->SPEED;

	int rd2 = rand() % 100;
	if (rd2 < rarity[0]) {
		int Speed = rand() % 20 + 5;
		Boots.amount = Speed;
		Boots.rarity = gameManager->COMMON;
	}
	else if (rd2 > rarity[0] && rd2 < (rarity[0] + rarity[1]))
	{
		int Speed = rand() % 41 + 21;
		Boots.amount = Speed;
		Boots.rarity = gameManager->RARE;
	}
	else if (rd2 > (rarity[0] + rarity[1]) && rd2 < (rarity[0] + rarity[1] + rarity[2]))
	{
		int Speed = rand() % 70 + 41;
		Boots.amount = Speed;
		Boots.rarity = gameManager->EPIC;
	}
	else if (rd2 > (rarity[0] + rarity[1] + rarity[2]) && rd2 < (rarity[0] + rarity[1] + rarity[2] + rarity[3]))
	{
		int Speed = rand() % 110 + 71;
		Boots.amount = Speed;
		Boots.rarity = gameManager->LEGENDARY;
	}

	Boots.level = 0;
	return Boots;
}