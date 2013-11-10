#include "Building.h"


Building::Building(BuildingType type, Side side)
{
	Building::side = side;
	buildingType = type;
}

Action Building::getActions(Side turn, UnitType unitType)
{
	if (side == turn)
	{
		return NONE;
	}
	else
	{
	}
}


Building::~Building(void)
{
}
