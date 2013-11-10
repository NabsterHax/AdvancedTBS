#pragma once

#include <allegro5\allegro.h>
#include "Tile.h"

class Map
{
private:
	const int width;
	const int height;
	const int terrainTileWidth;
	const int terrainTileHeight;
	const int terrainTileSheetCols;
	ALLEGRO_BITMAP* terrainTileSheet;
	Tile** tiles;
public:
	Map(int width, int height, ALLEGRO_BITMAP* terrainTileSheet);
	~Map(void);
	void Draw(float interpolation);
};

