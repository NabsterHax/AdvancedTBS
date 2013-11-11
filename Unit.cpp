#include "Unit.h"

#include "Globals.h"

#include <allegro5\allegro.h>

Unit::Unit(UnitType type)
{
	unitType = type;
	health = 10;

	moveRange = 0;
	for (int i = 0; i < terrainNumber; i++)
	{
		moveCosts[i] = -1;
	}
}


Unit::~Unit(void)
{
}