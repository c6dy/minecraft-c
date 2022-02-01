#ifndef VEC2_H
#define VEC2_H

#include <stdbool.h>

struct Vec2
{
	float x, y;
};

struct Vec2 vec2(float x, float y);
struct Vec2 vec2_zero();
struct Vec2 vec2_add(struct Vec2 a, struct Vec2 b);
struct Vec2 vec2_sub(struct Vec2 a, struct Vec2 b);
struct Vec2 vec2_inverse(struct Vec2 vec);
struct Vec2 vec2_normalize(struct Vec2 vec);
struct Vec2 vec2_scale(struct Vec2 vec, float scalar);
float vec2_dot(struct Vec2 a, struct Vec2 b);
float vec2_magnitude(struct Vec2 vec);
float vec2_distance(struct Vec2 a, struct Vec2 b);
bool vec2_equals(struct Vec2 a, struct Vec2 b);

#endif