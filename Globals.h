#pragma once

const int WIDTH = 1280;
const int HEIGHT = 720;

const int TICKRATE = 100;
const int MAX_FRAMESKIP = 5;

enum BuildingType {FACTORY, PORT, AIRPORT, CITY, HQ};
enum Action {CAPTURE, CREATE_UNIT, NONE};
enum UnitType {GROUND, AIR, SEA};
enum Side {RED, BLUE, EMPTY};
enum Terrain {GRASS, BEACH, ROAD, WATER, MOUNTAIN, FOREST};