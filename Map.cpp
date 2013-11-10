#include "Map.h"

#include <allegro5\allegro.h>
#include <allegro5/allegro_native_dialog.h>

#include "Globals.h"
#include "Tile.h"

Map::Map(int width, int height, ALLEGRO_BITMAP* terrainTileSheet) : 
	width(width), 
	height(height),
	terrainTileWidth(32),
	terrainTileHeight(32),
	terrainTileSheetCols(3)
{
	tiles = new Tile*[width];
	for(int i = 0; i < width; i++)
		tiles[i] = new Tile[height];

	this->terrainTileSheet = terrainTileSheet;
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
