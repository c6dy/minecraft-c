#include "mat4.h"
#include <math.h>
#include "mat3.h"
#include "util.h"

struct Mat4 mat4(struct Vec4 a, struct Vec4 b, struct Vec4 c, struct Vec4 d)
{
	return (struct Mat4){{ a, b, c, d }};
}

struct Mat4 mat4_zero()
{
	return mat4(
		vec4_zero(), 
		vec4_zero(), 
		vec4_zero(), 
		vec4_zero()
	);
}

struct Mat4 mat4_identity()
{	
	return mat4(
		vec4(1, 0, 0, 0),
		vec4(0, 1, 0, 0),
		vec4(0, 0, 1, 0),
		vec4(0, 0, 0, 1)
	);
}

struct Mat4 mat4_mul(struct Mat4 a, struct Mat4 b)
{
	struct Mat4 result = mat4_zero();

	for (int i = 0; i < 4; i++)
	{
		result.column[i].x = vec4_dot(mat4_row_0(a), b.column[i]);
		result.column[i].y = vec4_dot(mat4_row_1(a), b.column[i]);
		result.column[i].z = vec4_dot(mat4_row_2(a), b.column[i]);
		result.column[i].w = vec4_dot(mat4_row_3(a), b.column[i]);
	}

	return result;
}

struct Vec3 mat4_mul_vec3(struct Mat4 a, struct Vec3 vec3)
{
	struct Vec3 result = vec3_zero();
	
	result.x = (a.column[0].x * vec3.x) + (a.column[1].x * vec3.y) + (a.column[2].x * vec3.z) + (a.column[3].x * 1);
	result.y = (a.column[0].y * vec3.x) + (a.column[1].y * vec3.y) + (a.column[2].y * vec3.z) + (a.column[3].y * 1);
	result.z = (a.column[0].z * vec3.x) + (a.column[1].z * vec3.y) + (a.column[2].z * vec3.z) + (a.column[3].z * 1);

	return result;
}

struct Vec4 mat4_row_0(struct Mat4 a)
{
	return vec4(a.column[0].x, a.column[1].x, a.column[2].x, a.column[3].x);
}

struct Vec4 mat4_row_1(struct Mat4 a)
{
	return vec4(a.column[0].y, a.column[1].y, a.column[2].y, a.column[3].y);
}

struct Vec4 mat4_row_2(struct Mat4 a)
{
	return vec4(a.column[0].z, a.column[1].z, a.column[2].z, a.column[3].z);
}

struct Vec4 mat4_row_3(struct Mat4 a)
{
	return vec4(a.column[0].w, a.column[1].w, a.column[2].w, a.column[3].w);
}

// https://www.mathsisfun.com/algebra/matrix-determinant.html
float mat4_determinant(struct Mat4 a)
{
	return	+ a.column[0].x * mat4_minor(a, 0, 0)
			- a.column[1].x * mat4_minor(a, 1, 0)
			+ a.column[2].x * mat4_minor(a, 2, 0)
			- a.column[3].x * mat4_minor(a, 3, 0);
}



struct Mat4 mat4_cofactor(struct Mat4 mat)
{
	return mat4(
		vec4(mat4_minor(mat, 0, 0), -mat4_minor(mat, 0, 1), mat4_minor(mat, 0, 2), -mat4_minor(mat, 0, 3)),
		vec4(-mat4_minor(mat, 1, 0), mat4_minor(mat, 1, 1), -mat4_minor(mat, 1, 2), mat4_minor(mat, 1, 3)),
		vec4(mat4_minor(mat, 2, 0), -mat4_minor(mat, 2, 1), mat4_minor(mat, 2, 2), -mat4_minor(mat, 2, 3)),
		vec4(-mat4_minor(mat, 3, 0), mat4_minor(mat, 3, 1), -mat4_minor(mat, 3, 2), mat4_minor(mat, 3, 3))
	);
}

struct Mat4 mat4_adjugate(struct Mat4 mat)
{
	return mat4_transpose(mat4_cofactor(mat));
}

// Returns the determinant of the remaining 3x3 matrix after removing the specified column and row
float mat4_minor(struct Mat4 mat, int column, int row)
{	
	struct Mat3 minor;
	
	int current_column = 0;
	
	for(int i = 0; i < 4; i++)
	{	
		// column wasn't omitted
		if(i != column)
		{
			if(row == 0)
				minor.column[current_column] = vec3(mat.column[i].y, mat.column[i].z, mat.column[i].w);
			else if(row == 1)
				minor.column[current_column] = vec3(mat.column[i].x, mat.column[i].z, mat.column[i].w);
			else if(row == 2)
				minor.column[current_column] = vec3(mat.column[i].x, mat.column[i].y, mat.column[i].w);
			else if(row == 3)
				minor.column[current_column] = vec3(mat.column[i].x, mat.column[i].y, mat.column[i].z);
			
			current_column++;
		}
	}

	return mat3_determinant(minor);
}

struct Mat4 mat4_inverse(struct Mat4 mat)
{
	float det = mat4_determinant(mat);

	if(det != 0)
		return mat4_scale(mat4_adjugate(mat), 1/det);
	else
		return mat;
}

struct Mat4 mat4_transpose(struct Mat4 mat)
{
	return mat4(
		mat4_row_0(mat),
		mat4_row_1(mat),
		mat4_row_2(mat),
		mat4_row_3(mat)
	);
}


struct Mat4 mat4_scale(struct Mat4 a, float scalar)
{
	return mat4(
		vec4_scale(a.column[0], scalar),
		vec4_scale(a.column[1], scalar),
		vec4_scale(a.column[2], scalar),
		vec4_scale(a.column[3], scalar)
	);
}

struct Mat4 translate(struct Vec3 position)
{	
	struct Mat4 mat4 = mat4_identity();
	mat4.column[3] = vec4_from_vec3(position);
	return mat4;
}

struct Mat4 lookat(struct Vec3 eye, struct Vec3 center, struct Vec3 up_dir)
{
	struct Vec3 forward = vec3_normalize(vec3_sub(center, eye));
	struct Vec3 right = vec3_normalize(vec3_cross(forward, up_dir));
	struct Vec3 up = vec3_cross(right, forward);

	struct Mat4 v = {{
		{right.x, up.x, -forward.x, 0},
		{right.y, up.y, -forward.y, 0},
		{right.z, up.z, -forward.z, 0},
		{-vec3_dot(right, eye), -vec3_dot(up, eye), vec3_dot(forward, eye), 1}
	}};

	return v;
}

struct Mat4 perspective(float fov, float aspect, float near, float far)
{	
	float tanHalfFov = tan(radians(fov) / 2);

	struct Mat4 p = {{
		{1 / (aspect * tanHalfFov), 0, 0, 0},
		{0, 1 / tanHalfFov, 0, 0},
		{0, 0, - (far + near) / (far - near), -1},
		{0, 0, - (2 * far * near) / (far - near), 0}
	}};

	return p;
}
