#pragma once

#include "Globals.h"
#include "Building.h"
#include "Unit.h"

class Tile
{
private:
	Terrain terrain;
	Building* building;
	Unit* unit;
public:
	Tile();
	Tile(Terrain terrain);
	~Tile(void);
	Terrain getTerrain() const { return terrain; };
	void setTerrain(Terrain terrain) { this->terrain = terrain; };
	Unit* getUnit() const { return unit; }
	void setUnit(Unit* unit);
};

