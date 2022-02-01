#include "mat3.h"
#include "mat2.h"
#include "util.h"

struct Mat3 mat3(struct Vec3 a, struct Vec3 b, struct Vec3 c)
{
	return (struct Mat3){{ a, b, c }};
}

struct Mat3 mat3_zero()
{
	return mat3(vec3_zero(), vec3_zero(), vec3_zero());
}

struct Mat3 mat3_mul(struct Mat3 a, struct Mat3 b)
{
	struct Mat3 result = mat3_zero();

	for (int i = 0; i < 3; i++)
	{
		result.column[i].x = vec3_dot(mat3_row_0(a), b.column[i]);
		result.column[i].y = vec3_dot(mat3_row_1(a), b.column[i]);
		result.column[i].z = vec3_dot(mat3_row_2(a), b.column[i]);
	}

	return result;
}

struct Mat3 mat3_scale(struct Mat3 mat, float scalar)
{
	return mat3(
		vec3_scale(mat.column[0], scalar),
		vec3_scale(mat.column[1], scalar),
		vec3_scale(mat.column[2], scalar)
	);
}

struct Mat3 mat3_inverse(struct Mat3 mat)
{	
	float det = mat3_determinant(mat);

	if(det != 0)
	{
		float	a = mat.column[0].x, b = mat.column[1].x, c = mat.column[2].x,
				d = mat.column[0].y, e = mat.column[1].y, f = mat.column[2].y,
				g = mat.column[0].z, h = mat.column[1].z, i = mat.column[2].z;

		struct Mat3 m = mat3(
			vec3(e*i - f*h, f*g - d*i, d*h - e*g),
			vec3(c*h - b*i, a*i - c*g, b*g - a*h),
			vec3(b*f - c*e, c*d - a*f, a*e - b*d)
		);

		return mat3_scale(m, 1/det);
	}
	else
		return mat;
}

struct Mat3 mat3_transpose(struct Mat3 mat)
{	
	return mat3(
		mat3_row_0(mat),
		mat3_row_1(mat),
		mat3_row_2(mat)
	);
}

struct Vec3 mat3_mul_vec3(struct Mat3 mat, struct Vec3 vec)
{
	return vec3(
		vec3_dot(mat3_row_0(mat), vec),
		vec3_dot(mat3_row_1(mat), vec),
		vec3_dot(mat3_row_2(mat), vec)
	);
}

struct Vec3 mat3_row_0(struct Mat3 mat)
{
	return vec3(mat.column[0].x, mat.column[1].x, mat.column[2].x);
}

struct Vec3 mat3_row_1(struct Mat3 mat)
{
	return vec3(mat.column[0].y, mat.column[1].y, mat.column[2].y);
}

struct Vec3 mat3_row_2(struct Mat3 mat)
{
	return vec3(mat.column[0].z, mat.column[1].z, mat.column[2].z);
}

float mat3_minor(struct Mat3 mat, int column, int row)
{
	struct Mat2 minor;
	
	int current_column = 0;
	
	for(int i = 0; i < 3; i++)
	{	
		// column wasn't omitted
		if(i != column)
		{
			if(row == 0)
				minor.column[current_column] = vec2(mat.column[i].y, mat.column[i].z);
			else if(row == 1)
				minor.column[current_column] = vec2(mat.column[i].x, mat.column[i].z);
			else if(row == 2)
				minor.column[current_column] = vec2(mat.column[i].x, mat.column[i].y);

			current_column++;
		}
	}

	return mat2_determinant(minor);
}

// https://www.mathsisfun.com/algebra/matrix-determinant.html
float mat3_determinant(struct Mat3 mat)
{
	return mat.column[0].x * mat3_minor(mat, 0, 0) - mat.column[1].x * mat3_minor(mat, 1, 0) + mat.column[2].x * mat3_minor(mat, 2, 0);
}