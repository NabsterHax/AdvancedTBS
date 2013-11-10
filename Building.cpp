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

Action Building::getActions(Side turn, UnitType unitType)
{
	//If the unit is allied to the building
	if (side == turn)
	{
		return NONE;
	}
	else
	{
		//if (unitType == INFANTRY)
		//{
		//	return CAPTURE;
		//}
		//else
		//{
		//	return NONE;
		//}
	}
}


Building::~Building(void)
{
}
