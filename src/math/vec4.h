#ifndef VEC4_H
#define VEC4_H

#include "vec3.h"

struct Vec4
{
	float x, y, z, w;
};

struct Vec4 vec4(float x, float y, float z, float w);
struct Vec4 vec4_zero();
struct Vec4 vec4_add(struct Vec4 a, struct Vec4 b);
struct Vec4 vec4_sub(struct Vec4 a, struct Vec4 b);
struct Vec4 vec4_normalize(struct Vec4 a);
struct Vec4 vec4_scale(struct Vec4 a, float scalar);
struct Vec4 vec4_inverse(struct Vec4 a);
struct Vec4 vec4_from_vec3(struct Vec3 a);
float vec4_dot(struct Vec4 a, struct Vec4 b);
float vec4_magnitude(struct Vec4 a);

#endif