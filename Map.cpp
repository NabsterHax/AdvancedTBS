#include "Map.h"

#include <allegro5\allegro.h>
#include <allegro5/allegro_native_dialog.h>

#include "Globals.h"
#include "Tile.h"

Map::Map(int width, int height, ALLEGRO_BITMAP* terrainTileSheet, ALLEGRO_BITMAP* unitTileSheet) : 
	width(width), 
	height(height),
	terrainTileWidth(32),
	terrainTileHeight(32),
	terrainTileSheetCols(3),
	unitTileWidth(32),
	unitTileHeight(32),
	unitTileSheetCols(5)
{
	tiles = new Tile*[width];
	for(int i = 0; i < width; i++)
		tiles[i] = new Tile[height];

	this->terrainTileSheet = terrainTileSheet;
	this->unitTileSheet = unitTileSheet;
}


Map::~Map(void)
{
	for(int i = 0; i < width; i++)
		delete[] tiles[i];
	delete[] tiles;
}

void Map::Draw(float interpolation)
{
	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
		{
			al_draw_bitmap_region(terrainTileSheet,
				(tiles[i][j].getTerrain() % terrainTileSheetCols) * terrainTileWidth,
				(tiles[i][j].getTerrain() / terrainTileSheetCols) * terrainTileHeight,
				terrainTileWidth,
				terrainTileHeight,
				i*terrainTileWidth,
				j*terrainTileHeight,
				0);

			if(tiles[i][j].getUnit() != NULL)
			{
				al_draw_bitmap_region(unitTileSheet,
					((tiles[i][j].getUnit()->getUnitType()) % unitTileSheetCols) * unitTileWidth,
					((tiles[i][j].getUnit()->getUnitType()) / unitTileSheetCols) * unitTileHeight,
					unitTileWidth,
					unitTileHeight,
					i*terrainTileWidth,
					j*terrainTileHeight,
					0);
			}
		}
}

void Map::setTerrainAt(int x, int y, Terrain terrain)
{
	if(x > 0 && x < width && y > 0 && y < width)
		tiles[x][y].setTerrain(terrain);
	else
		al_show_native_message_box(NULL, "Error", "", 
			"terrain set out of map bounds", NULL, NULL);
}

void Map::setUnitAt(int x, int y, Unit* unit)
{
	if(x > 0 && x < width && y > 0 && y < width)
		tiles[x][y].setUnit(unit);
	else
		al_show_native_message_box(NULL, "Error", "", 
			"unit set out of map bounds", NULL, NULL);
}
