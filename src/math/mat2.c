#include "mat2.h"

struct Mat2 mat2(struct Vec2 a, struct Vec2 b)
{
	return (struct Mat2){{ a, b }};
}

struct Mat2 mat2_zero()
{
	return mat2(vec2_zero(), vec2_zero());
}

struct Mat2 mat2_identity()
{
	return mat2(vec2(1, 0), vec2(0, 1));
}

struct Mat2 mat2_mul(struct Mat2 a, struct Mat2 b)
{
	struct Mat2 result = mat2_zero();

	for (int i = 0; i < 2; i++)
	{
		result.column[i].x = vec2_dot(mat2_row_0(a), b.column[i]);
		result.column[i].y = vec2_dot(mat2_row_1(a), b.column[i]);
	}

	return result;
}

struct Mat2 mat2_scale(struct Mat2 a, float scalar)
{
	return mat2(vec2_scale(a.column[0], scalar), vec2_scale(a.column[1], scalar));
}

struct Mat2 mat2_inverse(struct Mat2 a)
{	
	float determinant = mat2_determinant(a);

	// cannot be inversed if the determinant is 0
	if(determinant == 0)
		return a;
	else
	{	
		// swap and negate values from the original matrix
		struct Mat2 swapped = mat2(vec2(a.column[1].y, -a.column[0].y), vec2(-a.column[1].x, a.column[0].x));
		return mat2_scale(swapped, 1/determinant);
	}
}

struct Mat2 mat2_transpose(struct Mat2 mat)
{
	return mat2(
		mat2_row_0(mat),
		mat2_row_1(mat)
	);
}

struct Vec2 mat2_row_0(struct Mat2 mat)
{
	return vec2(mat.column[0].x, mat.column[1].x);
}

struct Vec2 mat2_row_1(struct Mat2 mat)
{
	return vec2(mat.column[0].y, mat.column[1].y);
}

// https://www.mathsisfun.com/algebra/matrix-determinant.html
float mat2_determinant(struct Mat2 mat)
{
	return (mat.column[0].x * mat.column[1].y) - (mat.column[1].x * mat.column[0].y);
}