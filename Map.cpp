#include "Map.h"

#include <allegro5\allegro.h>
#include <allegro5/allegro_native_dialog.h>

#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

#include "Globals.h"
#include "Tile.h"

Map::Map(int width, int height, ALLEGRO_BITMAP* terrainTileSheet, ALLEGRO_BITMAP* buildingTileSheet, ALLEGRO_BITMAP* unitTileSheet) : 
	width(width), 
	height(height),
	tileWidth(64),
	tileHeight(64),
	terrainTileWidth(64),
	terrainTileHeight(64),
	terrainTileSheetCols(3),
	buildingTileWidth(32),
	buildingTileHeight(32),
	unitTileWidth(32),
	unitTileHeight(32),
	unitTileSheetCols(5)
	/*terrainTileWidth(32),
	terrainTileHeight(32),
	terrainTileSheetCols(3),
	buildingTileWidth(32),
	buildingTileHeight(32),
	unitTileWidth(32),
	unitTileHeight(32),
	unitTileSheetCols(5)*/
{
	mouseX = 0;
	mouseY = 0;

	tiles = new Tile*[width];
	for(int i = 0; i < width; i++)
		tiles[i] = new Tile[height];

	this->terrainTileSheet = terrainTileSheet;
	this->buildingTileSheet = buildingTileSheet;
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
			al_draw_tinted_bitmap_region(terrainTileSheet,
				(tiles[i][j].DrawOverlay() ? al_map_rgba_f(0.5, 0.5, 1, 1) : al_map_rgba_f(1, 1, 1, 1)),
				(tiles[i][j].getTerrain() % terrainTileSheetCols) * terrainTileWidth,
				(tiles[i][j].getTerrain() / terrainTileSheetCols) * terrainTileHeight,
				terrainTileWidth,
				terrainTileHeight,
				i*tileWidth,
				j*tileHeight,
				0);

			if(tiles[i][j].getBuilding() != NULL)
			{
				al_draw_bitmap_region(buildingTileSheet,
					tiles[i][j].getBuilding()->getBuildingType() * buildingTileWidth,
					tiles[i][j].getBuilding()->getSide() * buildingTileHeight,
					buildingTileWidth,
					buildingTileHeight,
					i*tileWidth,
					j*tileHeight,
					0);
			}

			if(tiles[i][j].getUnit() != NULL)
			{
				al_draw_bitmap_region(unitTileSheet,
					((tiles[i][j].getUnit()->getUnitType()) % unitTileSheetCols) * unitTileWidth,
					((tiles[i][j].getUnit()->getUnitType()) / unitTileSheetCols) * unitTileHeight,
					unitTileWidth,
					unitTileHeight,
					i*tileWidth,
					j*tileHeight,
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
	if(x >= 0 && x < width && y >= 0 && y < width)
		tiles[x][y].setUnit(unit);
	else
		al_show_native_message_box(NULL, "Error", "", 
			"unit set out of map bounds", NULL, NULL);
}

void Map::setBuildingAt(int x, int y, Building* building)
{
	if(x >= 0 && x < width && y >= 0 && y < width)
		tiles[x][y].setBuilding(building);
	else
		al_show_native_message_box(NULL, "Error", "", 
			"building set out of map bounds", NULL, NULL);
}

void Map::EventMouse(const ALLEGRO_EVENT& ev)
{
	if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		mouseX = ev.mouse.x;
		mouseY = ev.mouse.y;
	}
	else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		Coord coord = getMouseTile();

		/*std::stringstream dbgtxt;
		dbgtxt << "Mouse clicked at: " << coord.x << ", " << coord.y;
		al_show_native_message_box(NULL, "Debug", "", 
			dbgtxt.str().c_str(), NULL, NULL);*/

		if(tiles[coord.x][coord.y].getUnit() != NULL)
		{
			ClearTileOverlays();
			StartUnitMove(coord);
		}
	}
	else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{

	}
}

Coord Map::getMouseTile() const
{
	return Coord(mouseX / tileWidth, mouseY / tileHeight);
}

void Map::StartUnitMove(Coord coord)
{
	int** openNodes = new int*[width];
	for(int i = 0; i < width; i++)
	{
		openNodes[i] = new int[height];
		for(int j = 0; j < height; j++)
			openNodes[i][j] = -1;
	}

	FindPossibleMoves(coord, openNodes,
		tiles[coord.x][coord.y].getUnit()->getMoveRange(),
		tiles[coord.x][coord.y].getUnit()->getMoveCosts());

	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			if(openNodes[i][j] > -1)
			{
				tiles[i][j].setDrawOverlay(true);
			}
		}
		delete[] openNodes[i];
	}
	delete[] openNodes;
}

void Map::FindPossibleMoves(Coord coord, int** openNodes, int moveRange, int* moveCosts)
{
	if(moveRange <= openNodes[coord.x][coord.y])
		return;

	/*std::stringstream dbgtxt;
	dbgtxt << "Added coord: " << coord.x << ", " << coord.y
		<< "\n movesLeft: " << moveRange;
	al_show_native_message_box(NULL, "Debug", "", dbgtxt.str().c_str(), NULL, NULL);*/

	openNodes[coord.x][coord.y] = moveRange;
	int movesLeft;

	//Check up
	if(coord.y > 0 && moveCosts[tiles[coord.x][coord.y-1].getTerrain()] != -1)
	{
		movesLeft = moveRange - moveCosts[tiles[coord.x][coord.y-1].getTerrain()];
		if (movesLeft >= 0)
			FindPossibleMoves(Coord(coord.x, coord.y-1), openNodes, movesLeft, moveCosts);
	}

	//Check right
	if(coord.x < width-1 &&  moveCosts[tiles[coord.x+1][coord.y].getTerrain()] != -1)
	{
		movesLeft = moveRange - moveCosts[tiles[coord.x+1][coord.y].getTerrain()];
		if (movesLeft >= 0)
			FindPossibleMoves(Coord(coord.x+1, coord.y), openNodes, movesLeft, moveCosts);
	}

	//Check down
	if(coord.y < height-1 && moveCosts[tiles[coord.x][coord.y+1].getTerrain()] != -1)
	{
		movesLeft = moveRange - moveCosts[tiles[coord.x][coord.y+1].getTerrain()];
		if (movesLeft >= 0)
			FindPossibleMoves(Coord(coord.x, coord.y+1), openNodes, movesLeft, moveCosts);
	}

	//Check left
	if(coord.x > 0 && moveCosts[tiles[coord.x-1][coord.y].getTerrain()] != -1)
	{
		movesLeft = moveRange - moveCosts[tiles[coord.x-1][coord.y].getTerrain()];
		if (movesLeft >= 0)
			FindPossibleMoves(Coord(coord.x-1, coord.y), openNodes, movesLeft, moveCosts);
	}
}

void Map::ClearTileOverlays()
{
	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
			tiles[i][j].setDrawOverlay(false);
}