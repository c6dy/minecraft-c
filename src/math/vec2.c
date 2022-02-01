#include "vec2.h"
#include <stdio.h>
#include <math.h>

struct Vec2 vec2(float x, float y)
{
	return (struct Vec2){x, y};
}

struct Vec2 vec2_zero()
{
	return vec2(0, 0);
}

struct Vec2 vec2_add(struct Vec2 a, struct Vec2 b)
{
	return vec2(a.x + b.x, a.y + b.y);
}

struct Vec2 vec2_sub(struct Vec2 a, struct Vec2 b)
{
	return vec2(a.x - b.x, a.y - b.y);
}

struct Vec2 vec2_inverse(struct Vec2 vec)
{
	return vec2(-vec.x, -vec.y);
}

struct Vec2 vec2_normalize(struct Vec2 vec)
{
	float magnitude = vec2_magnitude(vec);
	return vec2(vec.x / magnitude, vec.y / magnitude);
}

struct Vec2 vec2_scale(struct Vec2 vec, float scalar)
{
	return vec2(vec.x * scalar, vec.y * scalar);
}

float vec2_dot(struct Vec2 a, struct Vec2 b)
{
	return (a.x * b.x) + (a.y * b.y);
}

float vec2_magnitude(struct Vec2 vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

float vec2_distance(struct Vec2 a, struct Vec2 b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool vec2_equals(struct Vec2 a, struct Vec2 b)
{
	return(a.x == b.x && a.y == b.y);
}