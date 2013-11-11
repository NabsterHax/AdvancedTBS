#include "Tile.h"

#include "Globals.h"

Tile::Tile()
{
	terrain = GRASS;
	building = NULL;
	unit = NULL;

	drawOverlay = false;
}

Tile::Tile(Terrain terrain) : terrain(terrain)
{
}


Tile::~Tile(void)
{
	if(building != NULL)
		delete building;
	if(unit != NULL)
		delete unit;
}

void Tile::setUnit(Unit* unit)
{
	if(this->unit != NULL)
		delete this->unit;
	this->unit = unit;
}

void Tile::setBuilding(Building* building)
{
	if(this->building != NULL)
		delete this->building;
	this->building = building;
}