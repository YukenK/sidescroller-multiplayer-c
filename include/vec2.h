#pragma once
#ifndef VEC2_H
#define VEC2_H
typedef struct {
	int x;
	int y;	
} Vec2;
Vec2 add_vec2(Vec2 a, Vec2 b);
Vec2 scale_vec2(Vec2 a, int scale);
Vec2 sub_vec2(Vec2 a, Vec2 b);
#endif
