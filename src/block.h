#ifndef BLOCK_H
#define BLOCK_H

#include "math/core.h"
#include <tidwall/hashmap.h>
#include "aabb.h"

// UV COORDINATE MATH (x, y)
// (x_index * tile_size) 		/ atlas_size, ((y_index + 1) * tile_size) 	/ atlas_size 	// top left
// (x_index * tile_size) 		/ atlas_size, (y_index  * tile_size) 		/ atlas_size 	// bottom left
// ((x_index + 1) * tile_size) 	/ atlas_size, (y_index * tile_size) 		/ atlas_size	// bottom right
// ((x_index + 1) * tile_size) 	/ atlas_size, ((y_index + 1) * tile_size) 	/ atlas_size 	// top right

// Block face vertices with offset applied
#define BLOCK_LEFT_TOPLEFT(x, y, z)			-0.5f + x, 0.5f  + y, -0.5f + z
#define BLOCK_LEFT_BOTTOMLEFT(x, y, z)		-0.5f + x, -0.5f + y, -0.5f + z
#define BLOCK_LEFT_BOTTOMRIGHT(x, y, z) 	-0.5f + x, -0.5f + y, 0.5f  + z
#define BLOCK_LEFT_TOPRIGHT(x, y, z) 		-0.5f + x, 0.5f  + y, 0.5f  + z

#define BLOCK_RIGHT_TOPLEFT(x, y, z)		0.5f + x, 0.5f  + y, 0.5f  + z
#define BLOCK_RIGHT_BOTTOMLEFT(x, y, z)		0.5f + x, -0.5f + y, 0.5f  + z
#define BLOCK_RIGHT_BOTTOMRIGHT(x, y, z) 	0.5f + x, -0.5f + y, -0.5f + z
#define BLOCK_RIGHT_TOPRIGHT(x, y, z) 		0.5f + x, 0.5f  + y, -0.5f + z

#define BLOCK_TOP_TOPLEFT(x, y, z)			-0.5f + x, 0.5f + y, -0.5f + z
#define BLOCK_TOP_BOTTOMLEFT(x, y, z)		-0.5f + x, 0.5f + y, 0.5f  + z
#define BLOCK_TOP_BOTTOMRIGHT(x, y, z) 		0.5f  + x, 0.5f + y, 0.5f  + z
#define BLOCK_TOP_TOPRIGHT(x, y, z) 		0.5f  + x, 0.5f + y, -0.5f + z

#define BLOCK_BOTTOM_TOPLEFT(x, y, z)		-0.5f + x, -0.5f + y, 0.5f  + z
#define BLOCK_BOTTOM_BOTTOMLEFT(x, y, z)	-0.5f + x, -0.5f + y, -0.5f + z
#define BLOCK_BOTTOM_BOTTOMRIGHT(x, y, z) 	0.5f  + x, -0.5f + y, -0.5f + z
#define BLOCK_BOTTOM_TOPRIGHT(x, y, z) 		0.5f  + x, -0.5f + y, 0.5f  + z

#define BLOCK_FRONT_TOPLEFT(x, y, z)		-0.5f + x, 0.5f  + y, 0.5f + z
#define BLOCK_FRONT_BOTTOMLEFT(x, y, z)		-0.5f + x, -0.5f + y, 0.5f + z
#define BLOCK_FRONT_BOTTOMRIGHT(x, y, z) 	0.5f  + x, -0.5f + y, 0.5f + z
#define BLOCK_FRONT_TOPRIGHT(x, y, z) 		0.5f  + x, 0.5f  + y, 0.5f + z

#define BLOCK_BACK_TOPLEFT(x, y, z)			0.5f  + x, 0.5f  + y, -0.5f + z
#define BLOCK_BACK_BOTTOMLEFT(x, y, z)		0.5f  + x, -0.5f + y, -0.5f + z
#define BLOCK_BACK_BOTTOMRIGHT(x, y, z) 	-0.5f + x, -0.5f + y, -0.5f + z
#define BLOCK_BACK_TOPRIGHT(x, y, z) 		-0.5f + x, 0.5f  + y, -0.5f + z

// Block face normals
#define BLOCK_NORMAL_LEFT 	-1.0f, 0.0f, 0.0f
#define BLOCK_NORMAL_RIGHT 	1.0f, 0.0f, 0.0f
#define BLOCK_NORMAL_TOP 	0.0f, 1.0f, 0.0f
#define BLOCK_NORMAL_BOTTOM 0.0f, -1.0f, 0.0f
#define BLOCK_NORMAL_FRONT 	0.0f, 0.0f, 1.0f
#define BLOCK_NORMAL_BACK 	0.0f, 0.0f, -1.0f

// Block face uv coords with offset applied
#define BLOCK_UV_TOPLEFT(x, y) 		0.0f  + x, 1.0f  + y
#define BLOCK_UV_BOTTOMLEFT(x, y) 	0.0f  + x, 0.75f + y
#define BLOCK_UV_BOTTOMRIGHT(x, y)	0.25f + x, 0.75f + y
#define BLOCK_UV_TOPRIGHT(x, y)		0.25f + x, 1.0f  + y

#define BLOCK_GRASS_TOP_OFFSET 	vec2(0.0f, 0.0f)
#define BLOCK_DIRT_OFFSET 		vec2(0.25f, 0.0f)
#define BLOCK_GRASS_OFFSET 		vec2(0.50f, 0.0f)
#define BLOCK_WATER_OFFSET		vec2(0.75f, 0.0f)
#define BLOCK_TREE_OFFSET		vec2(0.0f, -0.25f)
#define BLOCK_TREE_TOP_OFFSET	vec2(0.25f, -0.25f)
#define BLOCK_LEAF_OFFSET 		vec2(0.50f, -0.25f)
#define BLOCK_WOOD_OFFSET		vec2(0.75f, -0.25f)
#define BLOCK_SAND_OFFSET		vec2(0.0f, -0.50f)
#define BLOCK_STONE_OFFSET		vec2(0.25f, -0.50f)

struct Face
{
	float vertices[48];
};

enum BlockFace
{
	BLOCK_FRONT,
	BLOCK_BACK,
	BLOCK_LEFT,
	BLOCK_RIGHT,
	BLOCK_TOP,
	BLOCK_BOTTOM
};

enum BlockType
{
	BLOCK_AIR,
	BLOCK_DIRT,
	BLOCK_GRASS,
	BLOCK_WATER,
	BLOCK_SAND,
	BLOCK_TREE,
	BLOCK_LEAF,
	BLOCK_WOOD,
	BLOCK_STONE
};

struct Block
{	
	struct Vec3 position;
	struct Vec2 local_position;
	enum BlockType type;
	unsigned int index;
	char hash_string[32];
	bool top, bottom, render_first;
};

void block_get_left_face(struct Face *face, struct Vec3 position, struct Vec2 uv_offset);
void block_get_right_face(struct Face *face, struct Vec3 position, struct Vec2 uv_offset);
void block_get_top_face(struct Face *face, struct Vec3 position, struct Vec2 uv_offset);
void block_get_bottom_face(struct Face *face, struct Vec3 position, struct Vec2 uv_offset);
void block_get_front_face(struct Face *face, struct Vec3 position, struct Vec2 uv_offset);
void block_get_back_face(struct Face *face, struct Vec3 position, struct Vec2 uv_offset);
struct Vec2 block_get_uv_offset(enum BlockType, enum BlockFace);
struct AABB block_get_aabb(struct Vec3 position);
bool block_is_solid(struct Block *block);

void block_set_hash_string(struct Block *block);
int block_compare(const void *a, const void *b, void *vdata);
uint64_t block_hash(const void *item, uint64_t seed0, uint64_t seed1);

#endif