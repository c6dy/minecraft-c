#ifndef VEC3_H
#define VEC3_H

#include <stdbool.h>

struct Vec3
{
	float x, y, z;
};

struct Vec3 vec3(float x, float y, float z);
struct Vec3 vec3_zero();
struct Vec3 vec3_one();
struct Vec3 vec3_add(struct Vec3 a, struct Vec3 b);
struct Vec3 vec3_sub(struct Vec3 a, struct Vec3 b);
struct Vec3 vec3_cross(struct Vec3 a, struct Vec3 b);
struct Vec3 vec3_normalize(struct Vec3 a);
struct Vec3 vec3_scale(struct Vec3 a, float scalar);
struct Vec3 vec3_inverse(struct Vec3 a);
struct Vec3 vec3_round(struct Vec3 a);
float vec3_dot(struct Vec3 a, struct Vec3 b);
float vec3_magnitude(struct Vec3 a);
bool vec3_equals(struct Vec3 a, struct Vec3 b);

#endif