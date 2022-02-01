#include "world.h"
#include <time.h>
#include <stdlib.h>
#include "math/core.h"
#include <math.h>

void world_init(struct World *world)
{	
	// Randomize the world's seed
	srand(time(0));
	world->seed = rand() % __INT_MAX__;

	// Allocate space for 1 chunk
	world->chunks = malloc(sizeof(struct Chunk));
	world->chunk_count = 0;

	// Allocate enough space for 250 queued chunks
	world->queued_chunks = malloc(sizeof(struct QueuedChunk) * 250);
	world->queued_chunk_count = 0;

	// Create a hashmap for the world's chunks
	world->map = hashmap_new(sizeof(struct Chunk), 0, 0, 0, chunk_hash, chunk_compare, NULL, NULL);
	
	// Create 1 chunk starting at the origin and increment chunk count
	chunk_init(&world->chunks[world->chunk_count++], vec2(0, 0), world->seed, world->map, world);

	world->selected_block = BLOCK_GRASS;

	world->loaded = false;
}

void world_remove_block(struct World *world, struct Camera *camera, enum BlockType type)
{	
	for (int i = 0; i < world->chunk_count; i++)
	{	
		struct Chunk *chunk = &world->chunks[i];

		// Don't check invisible chunks
		if(!chunk->visible)
			continue;

		// Loop to check 4 block spaces from the camera's position
		for (size_t i = 1; i <= 4; i++)
		{	
			struct Vec3 target = vec3_round(vec3_add(vec3_scale(camera->target, i), camera->position));
			struct Block *block = hashmap_get(chunk->map, &(struct Block){.position = target});

			if(block_is_solid(block) && block->bottom == false)
			{	
				chunk->blocks[block->index].type = type;
				block->type = type;

				chunk_reload(chunk, world);

				// TO DO: Should only reload the chunk(s) that neighbor the block
				if(chunk_block_on_edge(chunk, block))
				{	
					struct Chunk *left  = hashmap_get(world->map, &(struct Chunk){.offset = vec2(chunk->offset.x - 16, chunk->offset.y)});
					struct Chunk *right = hashmap_get(world->map, &(struct Chunk){.offset = vec2(chunk->offset.x + 16, chunk->offset.y)});
					struct Chunk *front = hashmap_get(world->map, &(struct Chunk){.offset = vec2(chunk->offset.x, chunk->offset.y - 16)});
					struct Chunk *back  = hashmap_get(world->map, &(struct Chunk){.offset = vec2(chunk->offset.x, chunk->offset.y + 16)});

					chunk_reload(&world->chunks[left->index], world);
					chunk_reload(&world->chunks[right->index], world);
					chunk_reload(&world->chunks[front->index], world);
					chunk_reload(&world->chunks[back->index], world);	
				}
			
				return;
			}
		}    	
	}
}

void world_place_block(struct World *world, struct Camera *camera, enum BlockType type)
{
	for (int i = 0; i < world->chunk_count; i++)
	{	
		struct Chunk *chunk = &world->chunks[i];

		// Don't check invisible chunks
		if(!chunk->visible)
			continue;
		
		// Loop to check 4 block spaces from the camera's position
		for (size_t i = 1; i <= 4; i++)
		{	
			struct Vec3 target = vec3_round(vec3_add(vec3_scale(camera->target, i), camera->position));
			struct Block *block = hashmap_get(chunk->map, &(struct Block){.position = target});

			// Found block and block is not an air block
			if(block != NULL && block->type != BLOCK_AIR)
			{	
				struct Vec3 block_normal = vec3_sub(camera->position, block->position);
				block_normal = vec3_round(vec3_normalize(block_normal));
				chunk_add_block(chunk, vec3_add(block_normal, block->position), type);

				chunk_reload(chunk, world);

				return;
			}
		}    	
	}
}

void world_resize(struct World *world, struct Vec2 camera_position)
{	
	if(world->chunk_count == 769)
	{	
		world->queued_chunks = realloc(world->queued_chunks, sizeof(struct QueuedChunk) * 10);
		world->loaded = true;
	}
		

	// If there's a queued chunk, load it
	if(world->queued_chunk_count > 0)
	{	
		struct Vec2 offset = world->queued_chunks[world->queued_chunk_count - 1].offset;
		world_expand(world, offset);	
	}	

	int x = world->chunk_count;

	for (int i = 0; i < x; i++)
	{	
		struct Chunk *chunk = &world->chunks[i];

		for (int j = 0; j < 4; j++)
		{	
			// If the camera is less than 250 units away from an edge, expand in that direction
			if (vec2_distance(chunk->edges[j], camera_position) < 250)
			{
				if (!world_chunk_exists(world, chunk->edges[j]))			
					world_queue_chunk(world, chunk->edges[j]);				
				else
					chunk->visible = true;		
			}

			// If the camera is greater than 250 units away from the northern edge, hide the chunk
			// TO DO: Remove the chunk and free up memory
			if (vec2_distance(chunk->edges[0], camera_position) > 250)	
				chunk->visible = false;	
		}	
	}
}


struct Block* world_get_block(struct World *world, struct Vec3 position)
{	
	// -0 won't be recognized by the hashmap
	if(position.x == -0) position.x = 0;
	if(position.z == -0) position.z = 0;

	// Determine which chunk the block is in
	struct Vec2 chunk_offset = vec2(floor(position.x / CHUNK_WIDTH) * CHUNK_WIDTH,  floor(position.z / CHUNK_DEPTH) * CHUNK_DEPTH);

	// -0 won't be recognized by the hashmap
	if(chunk_offset.x == -0) chunk_offset.x = 0;
	if(chunk_offset.y == -0) chunk_offset.y = 0;

	struct Chunk *chunk = hashmap_get(world->map, &(struct Chunk){.offset = chunk_offset});

	if(chunk != NULL)
		return hashmap_get(chunk->map, &(struct Block){.position = position});
	else
		return NULL;
}

struct Chunk* world_expand(struct World *world, struct Vec2 offset)
{	
	world->chunks = realloc(world->chunks, sizeof(struct Chunk) * (world->chunk_count + 1));
	chunk_init(&world->chunks[world->chunk_count++], offset, world->seed, world->map, world);

	world->queued_chunk_count--;

	return &world->chunks[world->chunk_count - 1];
}

bool world_chunk_exists(struct World *world, struct Vec2 offset)
{	
	// Check queued chunks
	for (int i = 0; i < world->queued_chunk_count; i++)
	{
		if(vec2_equals(world->queued_chunks[i].offset, offset))
			return true;
	}
	
	// Check already loaded chunks
	return (hashmap_get(world->map, &(struct Chunk){.offset = offset}) != NULL);
}

void world_queue_chunk(struct World *world, struct Vec2 offset)
{	
	world->queued_chunks[world->queued_chunk_count].offset = offset;
	world->queued_chunk_count++;
}
