#pragma once

#include "Globals.h"
#include <allegro5\allegro.h>

class Unit
{
private:
	UnitType unitType;

protected:
	int health;
	int moveRange;
	int moveCosts [terrainNumber];

public:
	Unit(UnitType type);
	~Unit(void);
	
	UnitType getUnitType() const { return unitType; } ;
	int getMoveRange() const { return moveRange; }
	int* getMoveCosts() { return moveCosts; }
};

