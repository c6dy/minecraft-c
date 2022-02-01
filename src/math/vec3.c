#include "vec3.h"
#include <math.h>

struct Vec3 vec3(float x, float y, float z)
{
	return (struct Vec3){x, y, z};
}

struct Vec3 vec3_zero()
{
	return vec3(0.0f, 0.0f, 0.0f);
}

struct Vec3 vec3_one()
{
	return vec3(1.0f, 1.0f, 1.0f);
}

struct Vec3 vec3_add(struct Vec3 a, struct Vec3 b)
{
	return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

struct Vec3 vec3_sub(struct Vec3 a, struct Vec3 b)
{
	return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

struct Vec3 vec3_cross(struct Vec3 a, struct Vec3 b)
{
	return vec3((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x));
}

struct Vec3 vec3_normalize(struct Vec3 a)
{
	float magnitude = vec3_magnitude(a);
	return vec3(a.x / magnitude, a.y / magnitude, a.z / magnitude);
}

struct Vec3 vec3_scale(struct Vec3 a, float scalar)
{
	return vec3(a.x * scalar, a.y * scalar, a.z * scalar);
}

struct Vec3 vec3_inverse(struct Vec3 a)
{
	return vec3(-a.x, -a.y, -a.z);
}

struct Vec3 vec3_round(struct Vec3 a)
{
	return vec3(round(a.x), round(a.y), round(a.z));
}

float vec3_dot(struct Vec3 a, struct Vec3 b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

float vec3_magnitude(struct Vec3 a)
{
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

bool vec3_equals(struct Vec3 a, struct Vec3 b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}