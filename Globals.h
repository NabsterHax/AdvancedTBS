#pragma once

const int WIDTH = 1280;
const int HEIGHT = 720;

const int TICKRATE = 100;
const int MAX_FRAMESKIP = 5;

enum BuildingType {FACTORY, PORT, AIRPORT, CITY, HQ};
enum Action {NONE, CAPTURE, CREATE_UNIT};
enum UnitType {SOLDIER, MECH, RECON, TANK, HTANK, APC, ARTILERY, ROCKETS, AA, MISSILES, BSHIP, CRUISER, LANDER, SUB, FIGHTER, BOMBER, BCHOPPER, TCHOPPER};
enum Side {NEUTRAL, RED, BLUE};
enum Terrain {GRASS, BEACH, ROAD, WATER, MOUNTAIN, FOREST};
const int terrainNumber = 6;

struct Coord 
{
public:
	int x;
	int y;
	Coord() : x(0), y(0) {}
	Coord(int x, int y) : x(x), y(y) {}
	bool operator==(const Coord& a) { return (x == a.x) && (y == a.y); }
};