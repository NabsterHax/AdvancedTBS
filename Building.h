#pragma once

#include "Globals.h"

class Building
{
private:
	Side side;
	BuildingType buildingType;
public:
	Building(BuildingType type, Side side);
	~Building(void);
	Action getActions(Side turn);
	BuildingType getBuildingType() const { return buildingType; }
	Side getSide() const { return side; }
};

