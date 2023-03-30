#include "Gear.h"

Gear::Gear(db::gear* myGear)
{
	gear = myGear;
}


Gear::~Gear() {}

db::gear* Gear::getGear() {

	return gear;
}