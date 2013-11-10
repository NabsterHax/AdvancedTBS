#include "Building.h"


Building::Building(BuildingType type, Side side)
{
	Building::side = side;
	buildingType = type;
}

Action Building::getActions(Side turn)
{
	//If selecting allied building
	if (side == turn)
	{
		return CREATE_UNIT;
	}
	else
	{
		return NONE;
	}

}


Building::~Building(void)
{
}
