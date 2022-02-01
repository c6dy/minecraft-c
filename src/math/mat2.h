#ifndef MAT2_H
#define MAT2_H

#include "vec2.h"

struct Mat2
{
	struct Vec2 column[2];
};

struct Mat2 mat2(struct Vec2 a, struct Vec2 b);
struct Mat2 mat2_zero();
struct Mat2 mat2_identity();
struct Mat2 mat2_mul(struct Mat2 a, struct Mat2 b);
struct Mat2 mat2_scale(struct Mat2 a, float scalar);
struct Mat2 mat2_inverse(struct Mat2 a);
struct Mat2 mat2_transpose(struct Mat2 mat);
struct Vec2 mat2_row_0(struct Mat2 mat);
struct Vec2 mat2_row_1(struct Mat2 mat);
float mat2_determinant(struct Mat2 mat);

#endif