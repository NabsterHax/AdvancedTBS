#include "Mech.h"


Mech::Mech(void) : Unit(MECH)
{
	moveRange = 2;
	moveCosts[GRASS] = 1;
	moveCosts[BEACH] = 1;
	moveCosts[ROAD] = 1;
	moveCosts[MOUNTAIN] = 2;
	moveCosts[FOREST] = 1;
}


Mech::~Mech(void)
{
}
