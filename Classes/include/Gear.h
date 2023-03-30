#pragma once
#include "Database.h"
class Gear
{
protected:
	db::gear* gear;
public:
	Gear(db::gear*);
	~Gear();
	db::gear* getGear();
};