#include "vec4.h"
#include <math.h>

struct Vec4 vec4(float x, float y, float z, float w)
{
	return (struct Vec4){x, y, z, w};
}

struct Vec4 vec4_zero()
{
	return vec4(0, 0, 0, 0);
}

struct Vec4 vec4_add(struct Vec4 a, struct Vec4 b)
{
	return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

struct Vec4 vec4_sub(struct Vec4 a, struct Vec4 b)
{
	return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

struct Vec4 vec4_normalize(struct Vec4 a)
{
	float magnitude = vec4_magnitude(a);
	return vec4(a.x / magnitude, a.y / magnitude, a.z / magnitude, a.w / magnitude);
}

struct Vec4 vec4_scale(struct Vec4 a, float scalar)
{
	return vec4(a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar);
}

struct Vec4 vec4_inverse(struct Vec4 a)
{
	return vec4(-a.x, -a.y, -a.z, -a.w);
}

struct Vec4 vec4_from_vec3(struct Vec3 a)
{
	return vec4(a.x, a.y, a.z, 1);
}

float vec4_dot(struct Vec4 a, struct Vec4 b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

float vec4_magnitude(struct Vec4 a)
{
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}
