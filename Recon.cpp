#include "Recon.h"


Recon::Recon(void) : Unit(RECON)
{
	moveRange = 8;
	moveCosts[GRASS] = 2;
	moveCosts[BEACH] = 2;
	moveCosts[ROAD] = 1;
	moveCosts[FOREST] = 2;
}


Recon::~Recon(void)
{
}
