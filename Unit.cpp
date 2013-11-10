#include "Unit.h"

#include <allegro5\allegro.h>

Unit::Unit(UnitType type)
{
	unitType = type;
	health = 10;
}


Unit::~Unit(void)
{
}