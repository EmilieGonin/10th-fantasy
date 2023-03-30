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
	enemyLifeBar->setPosition(cocos2d::Vec2(200, 650));

	_player->update();
	//myLifeBar->drawPolygon(rectangle, 4, cocos2d::Color4F::GREEN, 1, cocos2d::Color4F::GREEN);
	//enemyLifeBar->drawPolygon(rectangle2, 4, cocos2d::Color4F::GREEN, 1, cocos2d::Color4F::GREEN);

	//Support Time 

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

					float rate = (effect[statIndex].rate / 100.0000);
					float amount = *_player->getTotalStats()[effect[statIndex].statId] * rate;
					CCLOG("%f", rate);
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
		multiplicatorType = *attacker->getTotalStats()[PATK];
		std::cout << "Physical damage" << std::endl;
	}
	else {
		usedDef = *target->getTotalStats()[MDEF];
		multiplicatorType = *attacker->getTotalStats()[MATK];
	}
	float atk = *attacker->getTotalStats()[ATK];
	int damage = (*attacker->getTotalStats()[ATK] + (*attacker->getTotalStats()[ATK] + multiplicatorType) - (usedDef / 2)) * skillUsed->getMultiplier();
	if (damage <= 0) {
		damage = 0;
	}
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
			
			if (selectedEnemy > - 1 && selectedSkill > -1)
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
				play();
				

			}
		}
	}
	updateLifeBar();
	battleCheck();

}

void Battle::battleCheck() {
	
	
	for (int i = 0; i < _battleOrder.size(); i++) {
		if (_battleOrder[i]->getBattleHP() <= 0) {
			CCLOG("I delete");
			_battleOrder.erase(_battleOrder.begin() + i );
		}
	}
	if (_battleOrder.size() == 1 && _player->getBattleHP() > 0) {
		CCLOG("I WIN");

		_battle = false;
		_win = true;
		cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
	}
	
}
/*
Gear Battle::drop() {

	int rarity = rand() % 4;
		switch (rarity)
		{
		case 0:
		default:
			break;
		}

	int type = rand() % 6;
	switch (type)
	{
	case 0:
	default:
		break;
	}

	int stat = rand() % statN;
	switch (stat)
	{
	case 0:
	default:
		break;
	}

	int amount = rand() % MaxStat;
	switch (Amount)
	{
	case 0:
	default:
		break;
	}


}*/

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
	enemyLifeBar->drawSolidRect(cocos2d::Vec2(0, 0), cocos2d::Vec2(250 * _enemies[0]->getBattleHP() / *_player->getTotalStats()[HP], 20), cocos2d::Color4F::RED);

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