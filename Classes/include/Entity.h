#pragma once
#include <vector>
#include <iostream>

class Entity
{
protected: 
	int _basehp, _basedef, _baseMagicDef, _baseatk, _bonusPhysical, _bonusMagical, _lvl, _spd, _critRate, _critDamage;
	int _totalHp, _totalDef, _totalMagicDef, _totalAtk, _totalPhysicalBonus, _totalMagicalBonus, _totalCritRate, _totalCritDamage;
	int _battleHp;

	bool _dmgType; // 0 physical, 1 magical

	std::vector<int*> _baseStats;
	std::vector<int*> _finalStats;// atk, matk, patk, mdef, pdef, hp, cr, cd

public:
	Entity();
	~Entity();

	//Getters
	int getSpd();
	int getBattleHP();
	int getDamageType();
	std::vector<int*> getBaseStats();
	std::vector<int*> getTotalStats();

	//Setters
	void looseHp(int);

	enum Stats {
		ATK = 0,
		MATK = 1,
		PATK = 2,
		MDEF = 3,
		PDEF = 4,
		HP = 5,
		CR = 6,
		CD = 7
	};
};