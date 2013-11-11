#pragma once

#include <allegro5\allegro.h>
#include <vector>
#include "Tile.h"
#include "Globals.h"

class Map
{
private:
	const int width;
	const int height;

	int mouseX;
	int mouseY;

	Tile** tiles;

	const int tileWidth;
	const int tileHeight;

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

	void StartUnitMove(Coord coord);
	void FindPossibleMoves(Coord coord, int** openNodes, int moveRange, int* moveCosts); 

public:
	Map(int width, int height, ALLEGRO_BITMAP* terrainTileSheet, ALLEGRO_BITMAP* buildingTileSheet, ALLEGRO_BITMAP* unitTileSheet);
	~Map(void);
	void Draw(float interpolation);

	void setTerrainAt(int x, int y, Terrain terrain);
	void setUnitAt(int x, int y, Unit* unit);
	void setBuildingAt(int x, int y, Building* building);

	void EventMouse(const ALLEGRO_EVENT& ev);
	Coord Map::getMouseTile() const;

	void ClearTileOverlays();
};

