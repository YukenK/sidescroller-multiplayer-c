#pragma once
#ifndef YUKMAP
#define YUKMAP
#include "vec.h"
enum TileType {
	NONE,
}
typedef struct {
	TileType type;
} Tile;
typedef struct {
	Tile* tiles;
	unsigned int width;
	unsigned int height;
} Map;
void init_map(Map* map, Vec2 dimensions);
Tile* get_tile(Map* map, Vec2 pos);
#endif
