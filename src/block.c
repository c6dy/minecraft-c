#include "block.h"
#include <stdio.h>
#include <string.h>

// block face triangle order: top left, bottom left, bottom right, top left, bottom right, top right

void block_get_left_face(struct Face *face, struct Vec3 position, struct Vec2 uv_offset)
{	
	*face = (struct Face)
	{{	
		BLOCK_LEFT_TOPLEFT(position.x, position.y, position.z),			BLOCK_NORMAL_LEFT,	BLOCK_UV_TOPLEFT(uv_offset.x, uv_offset.y),
		BLOCK_LEFT_BOTTOMLEFT(position.x, position.y, position.z),		BLOCK_NORMAL_LEFT,	BLOCK_UV_BOTTOMLEFT(uv_offset.x, uv_offset.y),
		BLOCK_LEFT_BOTTOMRIGHT(position.x, position.y, position.z),		BLOCK_NORMAL_LEFT,	BLOCK_UV_BOTTOMRIGHT(uv_offset.x, uv_offset.y),
		BLOCK_LEFT_TOPLEFT(position.x, position.y, position.z),			BLOCK_NORMAL_LEFT,	BLOCK_UV_TOPLEFT(uv_offset.x, uv_offset.y),
		BLOCK_LEFT_BOTTOMRIGHT(position.x, position.y, position.z),		BLOCK_NORMAL_LEFT,	BLOCK_UV_BOTTOMRIGHT(uv_offset.x, uv_offset.y),
		BLOCK_LEFT_TOPRIGHT(position.x, position.y, position.z),		BLOCK_NORMAL_LEFT,	BLOCK_UV_TOPRIGHT(uv_offset.x, uv_offset.y),
	}};
}

void block_get_right_face(struct Face *face, struct Vec3 position, struct Vec2 uv_offset)
{	
	*face = (struct Face)
	{{	
		BLOCK_RIGHT_TOPLEFT(position.x, position.y, position.z),		BLOCK_NORMAL_RIGHT,	BLOCK_UV_TOPLEFT(uv_offset.x, uv_offset.y),
		BLOCK_RIGHT_BOTTOMLEFT(position.x, position.y, position.z),		BLOCK_NORMAL_RIGHT,	BLOCK_UV_BOTTOMLEFT(uv_offset.x, uv_offset.y),
		BLOCK_RIGHT_BOTTOMRIGHT(position.x, position.y, position.z),	BLOCK_NORMAL_RIGHT,	BLOCK_UV_BOTTOMRIGHT(uv_offset.x, uv_offset.y),
		BLOCK_RIGHT_TOPLEFT(position.x, position.y, position.z),		BLOCK_NORMAL_RIGHT,	BLOCK_UV_TOPLEFT(uv_offset.x, uv_offset.y),
		BLOCK_RIGHT_BOTTOMRIGHT(position.x, position.y, position.z),	BLOCK_NORMAL_RIGHT,	BLOCK_UV_BOTTOMRIGHT(uv_offset.x, uv_offset.y),
		BLOCK_RIGHT_TOPRIGHT(position.x, position.y, position.z),		BLOCK_NORMAL_RIGHT,	BLOCK_UV_TOPRIGHT(uv_offset.x, uv_offset.y),
	}};
}

void block_get_top_face(struct Face *face, struct Vec3 position, struct Vec2 uv_offset)
{	
	*face = (struct Face)
	{{	
		BLOCK_TOP_TOPLEFT(position.x, position.y, position.z),			BLOCK_NORMAL_TOP,	BLOCK_UV_TOPLEFT(uv_offset.x, uv_offset.y),
		BLOCK_TOP_BOTTOMLEFT(position.x, position.y, position.z),		BLOCK_NORMAL_TOP,	BLOCK_UV_BOTTOMLEFT(uv_offset.x, uv_offset.y),
		BLOCK_TOP_BOTTOMRIGHT(position.x, position.y, position.z),		BLOCK_NORMAL_TOP,	BLOCK_UV_BOTTOMRIGHT(uv_offset.x, uv_offset.y),
		BLOCK_TOP_TOPLEFT(position.x, position.y, position.z),			BLOCK_NORMAL_TOP,	BLOCK_UV_TOPLEFT(uv_offset.x, uv_offset.y),
		BLOCK_TOP_BOTTOMRIGHT(position.x, position.y, position.z),		BLOCK_NORMAL_TOP,	BLOCK_UV_BOTTOMRIGHT(uv_offset.x, uv_offset.y),
		BLOCK_TOP_TOPRIGHT(position.x, position.y, position.z),			BLOCK_NORMAL_TOP,	BLOCK_UV_TOPRIGHT(uv_offset.x, uv_offset.y),
	}};
}

void block_get_bottom_face(struct Face *face, struct Vec3 position, struct Vec2 uv_offset)
{	
	*face = (struct Face)
	{{	
		BLOCK_BOTTOM_TOPLEFT(position.x, position.y, position.z),		BLOCK_NORMAL_BOTTOM,	BLOCK_UV_TOPLEFT(uv_offset.x, uv_offset.y),
		BLOCK_BOTTOM_BOTTOMLEFT(position.x, position.y, position.z),	BLOCK_NORMAL_BOTTOM,	BLOCK_UV_BOTTOMLEFT(uv_offset.x, uv_offset.y),
		BLOCK_BOTTOM_BOTTOMRIGHT(position.x, position.y, position.z),	BLOCK_NORMAL_BOTTOM,	BLOCK_UV_BOTTOMRIGHT(uv_offset.x, uv_offset.y),
		BLOCK_BOTTOM_TOPLEFT(position.x, position.y, position.z),		BLOCK_NORMAL_BOTTOM,	BLOCK_UV_TOPLEFT(uv_offset.x, uv_offset.y),
		BLOCK_BOTTOM_BOTTOMRIGHT(position.x, position.y, position.z),	BLOCK_NORMAL_BOTTOM,	BLOCK_UV_BOTTOMRIGHT(uv_offset.x, uv_offset.y),
		BLOCK_BOTTOM_TOPRIGHT(position.x, position.y, position.z),		BLOCK_NORMAL_BOTTOM,	BLOCK_UV_TOPRIGHT(uv_offset.x, uv_offset.y),
	}};
}

void block_get_front_face(struct Face *face, struct Vec3 position, struct Vec2 uv_offset)
{	
	*face = (struct Face)
	{{	
		BLOCK_FRONT_TOPLEFT(position.x, position.y, position.z),		BLOCK_NORMAL_FRONT,	BLOCK_UV_TOPLEFT(uv_offset.x, uv_offset.y),
		BLOCK_FRONT_BOTTOMLEFT(position.x, position.y, position.z),		BLOCK_NORMAL_FRONT,	BLOCK_UV_BOTTOMLEFT(uv_offset.x, uv_offset.y),
		BLOCK_FRONT_BOTTOMRIGHT(position.x, position.y, position.z),	BLOCK_NORMAL_FRONT,	BLOCK_UV_BOTTOMRIGHT(uv_offset.x, uv_offset.y),
		BLOCK_FRONT_TOPLEFT(position.x, position.y, position.z),		BLOCK_NORMAL_FRONT,	BLOCK_UV_TOPLEFT(uv_offset.x, uv_offset.y),
		BLOCK_FRONT_BOTTOMRIGHT(position.x, position.y, position.z),	BLOCK_NORMAL_FRONT,	BLOCK_UV_BOTTOMRIGHT(uv_offset.x, uv_offset.y),
		BLOCK_FRONT_TOPRIGHT(position.x, position.y, position.z),		BLOCK_NORMAL_FRONT,	BLOCK_UV_TOPRIGHT(uv_offset.x, uv_offset.y),
	}};
}

void block_get_back_face(struct Face *face, struct Vec3 position, struct Vec2 uv_offset)
{	
	*face = (struct Face)
	{{	
		BLOCK_BACK_TOPLEFT(position.x, position.y, position.z),			BLOCK_NORMAL_BACK,	BLOCK_UV_TOPLEFT(uv_offset.x, uv_offset.y),
		BLOCK_BACK_BOTTOMLEFT(position.x, position.y, position.z),		BLOCK_NORMAL_BACK,	BLOCK_UV_BOTTOMLEFT(uv_offset.x, uv_offset.y),
		BLOCK_BACK_BOTTOMRIGHT(position.x, position.y, position.z),		BLOCK_NORMAL_BACK,	BLOCK_UV_BOTTOMRIGHT(uv_offset.x, uv_offset.y),
		BLOCK_BACK_TOPLEFT(position.x, position.y, position.z),			BLOCK_NORMAL_BACK,	BLOCK_UV_TOPLEFT(uv_offset.x, uv_offset.y),
		BLOCK_BACK_BOTTOMRIGHT(position.x, position.y, position.z),		BLOCK_NORMAL_BACK,	BLOCK_UV_BOTTOMRIGHT(uv_offset.x, uv_offset.y),
		BLOCK_BACK_TOPRIGHT(position.x, position.y, position.z),		BLOCK_NORMAL_BACK,	BLOCK_UV_TOPRIGHT(uv_offset.x, uv_offset.y),
	}};
}

struct Vec2 block_get_uv_offset(enum BlockType type, enum BlockFace face)
{
	if(type == BLOCK_WATER)
		return BLOCK_WATER_OFFSET;

	if(type == BLOCK_TREE)
	{
		if(face == BLOCK_TOP || face == BLOCK_BOTTOM)
			return BLOCK_TREE_TOP_OFFSET;
		else
			return BLOCK_TREE_OFFSET;
	}

	if(type == BLOCK_SAND)
		return BLOCK_SAND_OFFSET;		

	if(type == BLOCK_DIRT)
		return BLOCK_DIRT_OFFSET;

	if(type == BLOCK_LEAF)
		return BLOCK_LEAF_OFFSET;

	if(type == BLOCK_WOOD)
		return BLOCK_WOOD_OFFSET;
	
	if(type == BLOCK_STONE)
		return BLOCK_STONE_OFFSET;

	if(type == BLOCK_GRASS)
	{
		if(face == BLOCK_TOP)
			return BLOCK_GRASS_TOP_OFFSET;
		else if(face == BLOCK_BOTTOM)
			return BLOCK_DIRT_OFFSET;
		else	
			return BLOCK_GRASS_OFFSET;
	}

	// Shouldn't reach here
	return BLOCK_GRASS_TOP_OFFSET;
}

struct AABB block_get_aabb(struct Vec3 position)
{
	return (struct AABB){vec3_add(position, vec3(-0.5f, -0.5f, -0.5f)), vec3_add(position, vec3(0.5f, 0.5f, 0.5f))};
}

bool block_is_solid(struct Block *block)
{	
	return(block != NULL && block->type != BLOCK_AIR && block->type != BLOCK_WATER);
}

void block_set_hash_string(struct Block *block)
{
	sprintf(block->hash_string, "%.0f, %.0f, %.0f", block->position.x, block->position.y, block->position.z);
}

int block_compare(const void *a, const void *b, void *vdata)
{	
	(void)vdata;
	const struct Block *b1 = a;
    const struct Block *b2 = b;
	return strcmp(b1->hash_string, b2->hash_string);
}

uint64_t block_hash(const void *item, uint64_t seed0, uint64_t seed1)
{
    struct Block *block = item;
	block_set_hash_string(block);
    return hashmap_sip(block->hash_string, strlen(block->hash_string), seed0, seed1);
}