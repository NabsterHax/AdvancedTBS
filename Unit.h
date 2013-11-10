#pragma once

#include "Globals.h"
#include <allegro5\allegro.h>

class Unit
{
private:
	UnitType unitType;
	int health;

public:
	Unit(UnitType type);
	~Unit(void);
	UnitType getUnitType() const { return unitType; } ;
};

