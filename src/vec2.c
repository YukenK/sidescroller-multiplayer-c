#include "vec2.h"
Vec2 add_vec2(Vec2 a, Vec2 b) {
	Vec2 c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}
Vec2 scale_vec2(Vec2 a, int scale) {
	Vec2 c;
	c.x = a.x * scale;
	c.y = a.y * scale;
	return c;
}
Vec2 sub_vec2(Vec2 a, Vec2 b) {
	Vec2 c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return c;
}
