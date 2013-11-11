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

	bool drawOverlay;
public:
	Tile();
	Tile(Terrain terrain);
	~Tile(void);

	Terrain getTerrain() const { return terrain; };
	void setTerrain(Terrain terrain) { this->terrain = terrain; }
	Building* getBuilding() const { return building; }
	void setBuilding(Building* building);
	Unit* getUnit() const { return unit; }
	void setUnit(Unit* unit);

	void setDrawOverlay(bool draw) { drawOverlay = draw; }
	bool DrawOverlay() const { return drawOverlay; }
};

