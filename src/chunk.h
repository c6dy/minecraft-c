#ifndef CHUNK_H
#define CHUNK_H

#include "math/core.h"
#include "block.h"
#include <tidwall/hashmap.h>
#include <stdbool.h>
#include "world.h"

#define CHUNK_WIDTH 16
#define CHUNK_DEPTH 16
#define CHUNK_HEIGHT 16
#define CHUNK_BLOCK_TOTAL CHUNK_WIDTH * CHUNK_DEPTH * CHUNK_HEIGHT
#define CHUNK_WATER_LEVEL 7

enum ChunkEdge
{
	CHUNK_NORTH,
	CHUNK_SOUTH,
	CHUNK_EAST,
	CHUNK_WEST
};

struct Chunk
{	
	unsigned int vao;
	struct Block *blocks;
	unsigned int block_count;
	struct Face *faces;
	int face_count;
	struct Vec2 offset, edges[4];
	bool visible;
	struct hashmap *map;
	char hash_string[16];
	unsigned int index;
};

struct World;

void chunk_init(struct Chunk *chunk, struct Vec2 offset, int seed, struct hashmap *world_map, struct World *world);
struct Block* chunk_get_block(struct Chunk *chunk, struct Vec3 position);
struct Block* chunk_add_block(struct Chunk *chunk, struct Vec3 position, enum BlockType type);
void chunk_build_tree(struct Chunk *chunk, struct Block *block, struct World *world);
void chunk_set_edges(struct Chunk *chunk);
void chunk_set_block_faces(struct Chunk *chunk, struct Block *block, struct World *world);
void chunk_reload(struct Chunk *chunk, struct World *world);
bool chunk_block_on_edge(struct Chunk *chunk, struct Block *block);

void chunk_set_hash_string(struct Chunk *chunk);
int chunk_compare(const void *a, const void *b, void *vdata);
uint64_t chunk_hash(const void *item, uint64_t seed0, uint64_t seed1);

#endif