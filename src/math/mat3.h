#ifndef MAT3_H
#define MAT3_H

#include "vec3.h"

struct Mat3
{
	struct Vec3 column[3];
};

struct Mat3 mat3(struct Vec3 a, struct Vec3 b, struct Vec3 c);
struct Mat3 mat3_zero();
struct Mat3 mat3_mul(struct Mat3 a, struct Mat3 b);
struct Mat3 mat3_scale(struct Mat3 mat, float scalar);
struct Mat3 mat3_inverse(struct Mat3 mat);
struct Mat3 mat3_transpose(struct Mat3 mat);
struct Vec3 mat3_mul_vec3(struct Mat3 mat, struct Vec3 vec);
struct Vec3 mat3_row_0(struct Mat3 mat);
struct Vec3 mat3_row_1(struct Mat3 mat);
struct Vec3 mat3_row_2(struct Mat3 mat);
float mat3_determinant(struct Mat3 mat);

#endif