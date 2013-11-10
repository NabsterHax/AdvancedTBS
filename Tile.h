#pragma once

#include "Globals.h"

class Tile
{
private:
	Terrain terrain;
	int building;
	int unit;
public:
	Tile();
	Tile(Terrain terrain);
	~Tile(void);
	Terrain getTerrain();
};

