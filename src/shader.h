#ifndef SHADER_H
#define SHADER_H

#include "math/core.h"

enum ShaderType
{
	SHADER_BLOCK,
	SHADER_AABB,
	SHADER_TYPE_COUNT
};

struct Shader
{
	unsigned int id;
};

struct Shader shader(const char *vertex_path, const char *fragment_path);
char *shader_read_file(const char *file_path);
void shader_set_vec2(unsigned int shader_id, const char *uniform, struct Vec2 *vec2);
void shader_set_vec3(unsigned int shader_id, const char *uniform, struct Vec3 *vec3);
void shader_set_mat4(unsigned int shader_id, const char *uniform, struct Mat4 *mat4);

#endif