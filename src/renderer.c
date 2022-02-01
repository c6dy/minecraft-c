#include <glad/glad.h>
#include "renderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void renderer_init(struct Renderer *renderer)
{	
	renderer_enable_settings();
	renderer_load_shaders(renderer);
	renderer_load_texture_atlas();
}

void renderer_enable_settings()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void renderer_load_shaders(struct Renderer *renderer)
{
	renderer->shaders[SHADER_BLOCK] = shader("data/shaders/block_vertex.glsl", "data/shaders/block_fragment.glsl");
	renderer->shaders[SHADER_AABB] = shader("data/shaders/aabb_vertex.glsl", "data/shaders/aabb_fragment.glsl");
}

void renderer_load_texture_atlas()
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// These settings prevent textures from bleeding into each other
	// https://gamedev.stackexchange.com/a/50777
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, channel_count;
	stbi_set_flip_vertically_on_load(1);
	unsigned char *data = stbi_load("data/textures/atlas.png", &width, &height, &channel_count, 0);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);

	stbi_image_free(data);
}

void renderer_load_chunk(struct Chunk *chunk)
{	
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &chunk->vao);

	glBindVertexArray(chunk->vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(struct Face) * chunk->face_count, chunk->faces, GL_STATIC_DRAW);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	// uv
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);
}

void renderer_use_shader(struct Renderer *renderer, enum ShaderType shader)
{
	glUseProgram(renderer->shaders[shader].id);
	renderer->shader = renderer->shaders[shader].id;
}

void renderer_clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.470f, 0.654f, 1.0f, 1.0f);
}

void renderer_draw_chunk(struct Renderer *renderer, struct Chunk *chunk)
{		
	renderer_use_shader(renderer, SHADER_BLOCK);
	glBindVertexArray(chunk->vao);
	glDrawArrays(GL_TRIANGLES, 0, 36 * chunk->face_count);
}