#include "Tile.h"

#include "Globals.h"

Tile::Tile()
{
	terrain = GRASS;
}

Tile::Tile(Terrain terrain) : terrain(terrain)
{
}


Tile::~Tile(void)
{
}

Terrain Tile::getTerrain()
{
	return terrain;
}

void Tile::setTerrain(Terrain terrain)
{
	this->terrain = terrain;
}