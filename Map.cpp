#include "Map.h"


Map::Map(const int width, const int height) : width(width), height(height)
{
	tiles = new Tile*[width];
	for(int i = 0; i < width; i++)
		tiles[i] = new Tile[height];
}


Map::~Map(void)
{
}
