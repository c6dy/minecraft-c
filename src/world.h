#ifndef WORLD_H
#define WORLD_H

#include "chunk.h"
#include <stdbool.h>
#include <tidwall/hashmap.h>
#include "camera.h"
#include "block.h"

struct QueuedChunk
{
	struct Vec2 offset;
};

struct World
{
	int seed;
	struct Chunk *chunks;
	int chunk_count;
	struct hashmap *map;
	struct QueuedChunk *queued_chunks;
	int queued_chunk_count;
	enum BlockType selected_block;
	bool loaded;
};

void world_init(struct World *world);
void world_remove_block(struct World *world, struct Camera *camera, enum BlockType type);
void world_place_block(struct World *world, struct Camera *camera, enum BlockType type);
void world_resize(struct World *world, struct Vec2 camera_position);
struct Chunk* world_expand(struct World *world, struct Vec2 offset);
bool world_chunk_exists(struct World *world, struct Vec2 offset);
struct Block* world_get_block(struct World *world, struct Vec3 position);
void world_queue_chunk(struct World *world, struct Vec2 offset);

#endif