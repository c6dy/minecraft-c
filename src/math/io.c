#include "io.h"
#include <stdio.h>

void vec2_print(struct Vec2 vec)
{
	printf("vec2(%f, %f)\n", vec.x, vec.y);
}

void vec3_print(struct Vec3 vec)
{
	printf("vec3(%f, %f, %f)\n", vec.x, vec.y, vec.z);
}

void vec4_print(struct Vec4 vec)
{
	printf("vec4(%f, %f, %f, %f)\n", vec.x, vec.y, vec.z, vec.w);
}

void mat2_print(struct Mat2 mat)
{
	printf("vec2(%f, %f)\n", mat.column[0].x, mat.column[0].y);
	printf("vec2(%f, %f)\n", mat.column[1].x, mat.column[1].y);
}

void mat3_print(struct Mat3 mat)
{	
	printf("vec3(%f, %f, %f)\n", mat.column[0].x, mat.column[0].y, mat.column[0].z);
	printf("vec3(%f, %f, %f)\n", mat.column[1].x, mat.column[1].y, mat.column[1].z);
	printf("vec3(%f, %f, %f)\n", mat.column[2].x, mat.column[2].y, mat.column[2].z);
}

void mat4_print(struct Mat4 mat)
{
	printf("vec4(%f, %f, %f, %f)\n", mat.column[0].x, mat.column[0].y, mat.column[0].z, mat.column[0].w);
	printf("vec4(%f, %f, %f, %f)\n", mat.column[1].x, mat.column[1].y, mat.column[1].z, mat.column[1].w);
	printf("vec4(%f, %f, %f, %f)\n", mat.column[2].x, mat.column[2].y, mat.column[2].z, mat.column[2].w);
	printf("vec4(%f, %f, %f, %f)\n", mat.column[3].x, mat.column[3].y, mat.column[3].z, mat.column[3].w);
}