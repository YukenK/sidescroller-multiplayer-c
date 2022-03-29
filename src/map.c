#include "map.h"
void init_map(Map* map, unsigned int width, unsigned int height) {
	map->width = width;
	map->height = height;
	map->tiles = malloc(sizeof(Tile) * width * height);
}
Tile* get_tile(Map* map, unsigned int x, unsigned int y) {
	return map->tiles + (x - 1) + ((y - 1) * map->width);
}

