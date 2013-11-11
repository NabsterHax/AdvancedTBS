#include "Soldier.h"
#include "Globals.h"


Soldier::Soldier(void) : Unit(SOLDIER)
{
	moveRange = 3;
	moveCosts[GRASS] = 1;
	moveCosts[BEACH] = 1;
	moveCosts[ROAD] = 1;
	moveCosts[MOUNTAIN] = 2;
	moveCosts[FOREST] = 1;
}


Soldier::~Soldier(void)
{
}
