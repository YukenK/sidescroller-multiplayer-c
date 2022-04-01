#pragma once
#ifndef MOVABLE_H
#define MOVABLE_H
#include "vec2.h"
typedef struct {
	unsigned int density;
	unsigned int map;
	Vec2 position;
} Movable;
#endif
