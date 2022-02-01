#ifndef MAT4_H
#define MAT4_H

#include "vec3.h"
#include "vec4.h"
#include "mat3.h"

struct Mat4
{
	struct Vec4 column[4];
};

struct Mat4 mat4(struct Vec4 a, struct Vec4 b, struct Vec4 c, struct Vec4 d);
struct Mat4 mat4_zero();
struct Mat4 mat4_identity();
struct Mat4 mat4_mul(struct Mat4 a, struct Mat4 b);
struct Mat4 mat4_inverse(struct Mat4 mat);
struct Mat4 mat4_transpose(struct Mat4 mat);
struct Mat4 mat4_scale(struct Mat4 a, float scalar);

float mat4_determinant(struct Mat4 a);
float mat4_minor(struct Mat4 mat, int column, int row);

struct Vec3 mat4_mul_vec3(struct Mat4 a, struct Vec3 vec3);

struct Vec4 mat4_row_0(struct Mat4 a);
struct Vec4 mat4_row_1(struct Mat4 a);
struct Vec4 mat4_row_2(struct Mat4 a);
struct Vec4 mat4_row_3(struct Mat4 a);

struct Mat4 translate(struct Vec3 position);
struct Mat4 lookat(struct Vec3 eye, struct Vec3 center, struct Vec3 up_dir);
struct Mat4 perspective(float fov, float aspect, float near, float far);

#endif