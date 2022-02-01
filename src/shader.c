#include "shader.h"
#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>

struct Shader shader(const char *vertex_path, const char *fragment_path)
{
	struct Shader shader;
	shader.id = glCreateProgram();

	const char *vertex_shader_src = shader_read_file(vertex_path);
	const char *fragment_shader_src = shader_read_file(fragment_path);

	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
	glCompileShader(vertex_shader);

	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
	glCompileShader(fragment_shader);

	glAttachShader(shader.id, vertex_shader);
	glAttachShader(shader.id, fragment_shader);

	glLinkProgram(shader.id);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	free((void *)vertex_shader_src);
	free((void *)fragment_shader_src);

	return shader;
}

char *shader_read_file(const char *file_path)
{
	FILE *fp = fopen(file_path, "r");

	if(fp == NULL)
	{
		printf("Could not open file: %s\n", file_path);
		exit(-1);
	}
	
	char *string = malloc(10000);

	fread(string, 1, 10000, fp);

	fclose(fp);

	return string;
}

void shader_set_vec2(unsigned int shader_id, const char *uniform, struct Vec2 *vec2)
{
	glUniform2fv(glGetUniformLocation(shader_id, uniform), 1, (const GLfloat *)vec2);
}

void shader_set_vec3(unsigned int shader_id, const char *uniform, struct Vec3 *vec3)
{
	glUniform3fv(glGetUniformLocation(shader_id, uniform), 1, (const GLfloat *)vec3);
}

void shader_set_mat4(unsigned int shader_id, const char *uniform, struct Mat4 *mat4)
{
	glUniformMatrix4fv(glGetUniformLocation(shader_id, uniform), 1, GL_FALSE, (const GLfloat *)mat4);
}