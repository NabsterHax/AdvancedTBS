#pragma once

#include <allegro5\allegro.h>
#include "Tile.h"

class Map
{
private:
	const int width;
	const int height;

	Tile** tiles;

	const int terrainTileWidth;
	const int terrainTileHeight;
	const int terrainTileSheetCols;
	ALLEGRO_BITMAP* terrainTileSheet;

	const int buildingTileWidth;
	const int buildingTileHeight;
	ALLEGRO_BITMAP* buildingTileSheet;

	const int unitTileWidth;
	const int unitTileHeight;
	const int unitTileSheetCols;
	ALLEGRO_BITMAP* unitTileSheet;

public:
	Map(int width, int height, ALLEGRO_BITMAP* terrainTileSheet, ALLEGRO_BITMAP* buildingTileSheet, ALLEGRO_BITMAP* unitTileSheet);
	~Map(void);
	void Draw(float interpolation);
	void setTerrainAt(int x, int y, Terrain terrain);
	void setUnitAt(int x, int y, Unit* unit);
	void setBuildingAt(int x, int y, Building* building);
};

