#include "chunk.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define FNL_IMPL
#include <fastnoiselite/fastnoiselite.h>
#include "renderer.h"

void chunk_init(struct Chunk *chunk, struct Vec2 offset, int seed, struct hashmap *world_map, struct World *world)
{
	// Create a hashmap for the chunk blocks
	chunk->map = hashmap_new(sizeof(struct Block), 0, 0, 0, block_hash, block_compare, NULL, NULL);

	chunk->offset = offset;
	chunk->index = world->chunk_count-1;

	hashmap_set(world_map, chunk);

	chunk->visible = true;

	chunk->faces = malloc(sizeof(struct Face));
	chunk->face_count = 0;

	// Set chunk edges
	chunk_set_edges(chunk);
	
	// Create noise state
	fnl_state noise = fnlCreateState();
	noise.noise_type = FNL_NOISE_PERLIN;
	noise.seed = seed;
	noise.fractal_type = FNL_FRACTAL_RIDGED;

	chunk->blocks = calloc(CHUNK_BLOCK_TOTAL, sizeof(struct Block));
	chunk->block_count = CHUNK_BLOCK_TOTAL;

	int current_index = 0;

	//Build chunk
	for (int x = 0; x < CHUNK_WIDTH; x++)
	{
		for (int z = 0; z < CHUNK_DEPTH; z++)
		{	
			struct Block *block = &chunk->blocks[current_index];
			block->index = current_index;
			block->top = true;
			block->render_first = true;
			current_index++;

			float noise3d = fnlGetNoise2D(&noise, x + offset.x, z + offset.y);
			float block_height = round(CHUNK_HEIGHT * noise3d);

			block->position = vec3(x + offset.x, block_height, z + offset.y);
			block->local_position = vec2(x, z);

			block->type = BLOCK_GRASS;

			if(block_height <= CHUNK_WATER_LEVEL)
			{
				block->type = BLOCK_WATER;
				block->position.y = CHUNK_WATER_LEVEL;
			}

			if(block_height == CHUNK_WATER_LEVEL + 1)
				block->type = BLOCK_SAND;

			hashmap_set(chunk->map, block);

			// Build blocks downwards
			for (int y = 1; y < 16; y++)
			{	
				struct Block *b = &chunk->blocks[current_index];
				b->index = current_index;
				b->position = vec3(block->position.x, block->position.y-y, block->position.z);
				b->local_position = vec2(x, z);
				b->type = block->type;
				b->top = false;
				b->render_first = false;
			
				if(block->type == BLOCK_WATER)
				{	
					// Make blocks under the water sand
					b->type = BLOCK_SAND;

					// Make the sand blocks start further below the water
					b->position.y -= 1;
				}
				
				// Make the first blocks down the y axis get drawn in the initial render
				if(y <= 2)
					b->render_first = true;

				if(y == 15)
				{
					b->bottom = true;
					b->type = BLOCK_STONE;
				}
					
					
				hashmap_set(chunk->map, b);

				current_index++;
			}

		}
			
	}

	for (int i = 0; i < CHUNK_BLOCK_TOTAL; i++)
	{	
		struct Block block = chunk->blocks[i];

		// Check if there's nothing on top of the block, and it's a grass block
		if(block.top && block.type == BLOCK_GRASS && rand() % 300 == 1)	
			chunk_build_tree(chunk, &block, world);

		if(block.type != BLOCK_AIR && block.render_first)
			chunk_set_block_faces(chunk, &block, world);
	}

	renderer_load_chunk(chunk);
	free(chunk->faces);
}

struct Block* chunk_add_block(struct Chunk *chunk, struct Vec3 position, enum BlockType type)
{	
	// Check if there's a block in the position, if there is, just change the block type
	struct Block *block = hashmap_get(chunk->map, &(struct Block){.position = position});
	if(block != NULL)
	{
		chunk->blocks[block->index].type = type;
		block->type = type;
		return block;
	}

	// Allocate space for another block
	chunk->blocks = realloc(chunk->blocks, sizeof(struct Block) * (chunk->block_count + 1));

	chunk->blocks[chunk->block_count].position = position;
	chunk->blocks[chunk->block_count].type = type;
	chunk->blocks[chunk->block_count].index = chunk->block_count;

	// Place the new block in the hashmap
	hashmap_set(chunk->map, &chunk->blocks[chunk->block_count]);

	// Return the new block and increment the block count
	return &chunk->blocks[chunk->block_count++];
}

struct Block* chunk_get_block(struct Chunk *chunk, struct Vec3 position)
{	
    return hashmap_get(chunk->map, &(struct Block){.position = position});
}

void chunk_build_tree(struct Chunk *chunk, struct Block *block, struct World *world)
{
	struct Block *tree_top;

	// Build tree trunk
	for (int i = 1; i <= 5; i++)
	{	
		tree_top = chunk_add_block(chunk, vec3_add(block->position, vec3(0, i, 0)), BLOCK_TREE);
		chunk_set_block_faces(chunk, tree_top, world);
	}

	struct Vec3 tree_top_pos = tree_top->position;

	//Build leaves (bottom layer)
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			for (int z = 0; z < 5; z++)
			{
				struct Block *block = chunk_add_block(chunk, vec3_add(tree_top_pos, vec3(x-2, y, z-2)), BLOCK_LEAF);
				chunk_set_block_faces(chunk, block, world);
			}	
		}
	}

	// Build leaves (middle layer)
	for (int x = 0; x < 3; x++)
	{
		for (int y = 2; y < 4; y++)
		{
			for (int z = 0; z < 3; z++)
			{
				struct Block *block = chunk_add_block(chunk, vec3_add(tree_top_pos, vec3(x-1, y, z-1)), BLOCK_LEAF);
				chunk_set_block_faces(chunk, block, world);
			}	
		}
	}

	//Build leaves (top)
	{
		struct Block *block = chunk_add_block(chunk, vec3_add(tree_top_pos, vec3(0, 4, 0)), BLOCK_LEAF);
		chunk_set_block_faces(chunk, block, world);
	}
}

void chunk_set_edges(struct Chunk *chunk)
{
	chunk->edges[CHUNK_NORTH] 	= vec2_add(chunk->offset, vec2(0, -CHUNK_DEPTH));
	chunk->edges[CHUNK_SOUTH] 	= vec2_add(chunk->offset, vec2(0, CHUNK_DEPTH));
	chunk->edges[CHUNK_EAST]  	= vec2_add(chunk->offset, vec2(CHUNK_WIDTH, 0));
	chunk->edges[CHUNK_WEST]	= vec2_add(chunk->offset, vec2(-CHUNK_WIDTH, 0));
}

void chunk_set_block_faces(struct Chunk *chunk, struct Block *block, struct World *world)
{	
	struct Block *left   = world_get_block(world, vec3_add(block->position, vec3(-1, 0, 0)));
	struct Block *right  = world_get_block(world, vec3_add(block->position, vec3(1, 0, 0)));
	struct Block *top    = world_get_block(world, vec3_add(block->position, vec3(0, 1, 0)));
	struct Block *bottom = world_get_block(world, vec3_add(block->position, vec3(0, -1, 0)));
	struct Block *front  = world_get_block(world, vec3_add(block->position, vec3(0, 0, 1)));
	struct Block *back   = world_get_block(world, vec3_add(block->position, vec3(0, 0, -1)));

	if (!block_is_solid(left) && block->type != BLOCK_WATER) {
		chunk->faces = realloc(chunk->faces, sizeof(struct Face) * (chunk->face_count + 1));
		block_get_left_face(&chunk->faces[chunk->face_count++], block->position, block_get_uv_offset(block->type, BLOCK_LEFT));
	}		
		
	if (!block_is_solid(right) && block->type != BLOCK_WATER) {
		chunk->faces = realloc(chunk->faces, sizeof(struct Face) * (chunk->face_count + 1));
		block_get_right_face(&chunk->faces[chunk->face_count++], block->position, block_get_uv_offset(block->type, BLOCK_RIGHT));
	}	
		
	if (!block_is_solid(top)) {
		chunk->faces = realloc(chunk->faces, sizeof(struct Face) * (chunk->face_count + 1));
		block_get_top_face(&chunk->faces[chunk->face_count++], block->position, block_get_uv_offset(block->type, BLOCK_TOP));
	}
				
	if (!block_is_solid(bottom) && block->type != BLOCK_WATER && !block->bottom) {
		chunk->faces = realloc(chunk->faces, sizeof(struct Face) * (chunk->face_count + 1));
		block_get_bottom_face(&chunk->faces[chunk->face_count++], block->position, block_get_uv_offset(block->type, BLOCK_BOTTOM));
	}
		
	if (!block_is_solid(front) && block->type != BLOCK_WATER) {
		chunk->faces = realloc(chunk->faces, sizeof(struct Face) * (chunk->face_count + 1));
		block_get_front_face(&chunk->faces[chunk->face_count++], block->position, block_get_uv_offset(block->type, BLOCK_FRONT));
	}
		
		
	if (!block_is_solid(back) && block->type != BLOCK_WATER) {
		chunk->faces = realloc(chunk->faces, sizeof(struct Face) * (chunk->face_count + 1));
		block_get_back_face(&chunk->faces[chunk->face_count++], block->position, block_get_uv_offset(block->type, BLOCK_BACK));
	}
		
}

void chunk_reload(struct Chunk *chunk, struct World *world)
{
	chunk->face_count = 0;
	chunk->faces = malloc(sizeof(struct Face));

	for (int i = 0; i < chunk->block_count; i++)
	{
		if(chunk->blocks[i].type != BLOCK_AIR)
			chunk_set_block_faces(chunk, &chunk->blocks[i], world);
	}
		
	renderer_load_chunk(chunk);
	free(chunk->faces);
}

bool chunk_block_on_edge(struct Chunk *chunk, struct Block *block)
{
	return(	block->local_position.x == 0 	||
			block->local_position.x == 15 	||
			block->local_position.y == 0	||
			block->local_position.y == 15
	);
}


void chunk_set_hash_string(struct Chunk *chunk)
{	
	sprintf(chunk->hash_string, "%.0f, %.0f", chunk->offset.x, chunk->offset.y);
}

int chunk_compare(const void *a, const void *b, void *vdata)
{
	(void)vdata;
	const struct Chunk *c1 = a;
    const struct Chunk *c2 = b;
	return strcmp(c1->hash_string, c2->hash_string);
}

uint64_t chunk_hash(const void *item, uint64_t seed0, uint64_t seed1)
{
	struct Chunk *chunk = item;
	chunk_set_hash_string(chunk);
    return hashmap_sip(chunk->hash_string, strlen(chunk->hash_string), seed0, seed1);
}
