#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"
#include "chunk.h"
#include "camera.h"

struct Renderer
{
    struct Shader shaders[SHADER_TYPE_COUNT];
    unsigned int shader;
};

void renderer_init(struct Renderer *renderer);
void renderer_enable_settings();
void renderer_load_shaders(struct Renderer *renderer);
void renderer_load_texture_atlas();
void renderer_load_chunk(struct Chunk *chunk);
void renderer_use_shader(struct Renderer *renderer, enum ShaderType shader);
void renderer_clear();
void renderer_draw_chunk(struct Renderer *renderer, struct Chunk *chunk);

#endif