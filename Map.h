#pragma once

#include "Tile.h"

class Map
{
private:
	const int width;
	const int height;
	Tile ** tiles;
public:
	Map(int width, int height);
	~Map(void);
};

