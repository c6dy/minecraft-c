#include "physics.h"
#include <stdio.h>

void physics_simulate(struct World *world, void *rb, float delta_time)
{
	struct Camera *camera = rb;

	if(!camera->free)
		camera->force = vec3_add(camera->force, GRAVITY);

	// Kill the velocity if the camera is in free fly mode
	if(camera->free)
		camera->velocity = vec3(0,0,0);

	// Calculate acceleration
	struct Vec3 acceleration = vec3_scale(camera->force, 1/camera->mass);

	// Calculate velocity
	camera->velocity = vec3_add(camera->velocity, vec3_scale(acceleration, PHYSICS_TIMESTEP));

	// Clear forces
	camera->force = vec3(0, 0, 0);

	// Update position
	camera->position = vec3_add(camera->position, vec3_scale(camera->velocity, PHYSICS_TIMESTEP));
	camera_update_aabb(camera);

	physics_check_aabbs(world, camera);
	camera_update_aabb(camera);

	// Dampen x and z velocity values
	camera->velocity.x *= 0.90;
	camera->velocity.z *= 0.90;
}


void physics_check_aabbs(struct World *world, struct Camera *camera)
{	
	struct Block *bottom = world_get_block(world, vec3_round(vec3(camera->position.x, camera->position.y - 2, camera->position.z)));
		
	if(block_is_solid(bottom))
	{	
		struct AABB block_aabb = block_get_aabb(bottom->position);

		// Check for penetration, also check camera velocity to make sure this won't activate while jumping
		if(physics_aabbs_overlap(camera->aabb, block_aabb)  && camera->velocity.y <= 0)
		{	
			camera->jumping = false;
			camera->velocity.y = 0;
			camera->position.y = bottom->position.y + 2.0f;
		}
	}

	struct Block *top = world_get_block(world, vec3_round(vec3_add(camera->position, vec3(0, 1, 0))));
	if(block_is_solid(top))
	{	

		struct AABB block_aabb = block_get_aabb(top->position);
		if(physics_aabbs_overlap(camera->aabb, block_aabb))
		{
			camera->velocity.y = 0;
			camera->position.y = top->position.y - 1.0f;
		}
	}

	struct Block *left = world_get_block(world, vec3_round(vec3_add(camera->position, vec3(-1, -1, 0))));
	if(block_is_solid(left))
	{	
		struct AABB block_aabb = block_get_aabb(left->position);

		if(physics_aabbs_overlap(camera->aabb, block_aabb))
		{	
			camera->velocity.x = 0;
			camera->position.x = left->position.x + 1.0f;
		}
	}
	struct Block *left2 = world_get_block(world, vec3_round(vec3_add(camera->position, vec3(-1, 0, 0))));
	if(block_is_solid(left2))
	{	
		struct AABB block_aabb = block_get_aabb(left2->position);

		if(physics_aabbs_overlap(camera->aabb, block_aabb))
		{	
			camera->velocity.x = 0;
			camera->position.x = left2->position.x + 1.0f;
		}
	}

	struct Block *right = world_get_block(world, vec3_round(vec3_add(camera->position, vec3(1, -1, 0))));
	if(block_is_solid(right))
	{
		struct AABB block_aabb = block_get_aabb(right->position);
		
		if(physics_aabbs_overlap(camera->aabb, block_aabb))
		{	
			
			camera->velocity.x = 0;	
			camera->position.x = right->position.x - 1.0f;
		}
			
	}

	struct Block *right2 = world_get_block(world, vec3_round(vec3_add(camera->position, vec3(1, 0, 0))));
	if(block_is_solid(right2))
	{
		struct AABB block_aabb = block_get_aabb(right2->position);
		
		if(physics_aabbs_overlap(camera->aabb, block_aabb))
		{	
			
			camera->velocity.x = 0;	
			camera->position.x = right2->position.x - 1.0f;
		}
			
	}

	struct Block *front = world_get_block(world, vec3_round(vec3_add(camera->position, vec3(0, -1, -1))));
	if(block_is_solid(front))
	{	
		struct AABB block_aabb = block_get_aabb(front->position);

		if(physics_aabbs_overlap(camera->aabb, block_aabb))	
		{
			camera->velocity.z = 0;
			camera->position.z = front->position.z + 1.0f;
		}
			
	}

	struct Block *front2 = world_get_block(world, vec3_round(vec3_add(camera->position, vec3(0, 0, -1))));
	if(block_is_solid(front2))
	{	
		struct AABB block_aabb = block_get_aabb(front2->position);

		if(physics_aabbs_overlap(camera->aabb, block_aabb))	
		{
			camera->velocity.z = 0;
			camera->position.z = front2->position.z + 1.0f;
		}
			
	}
	
	struct Block *back = world_get_block(world, vec3_round(vec3_add(camera->position, vec3(0, -1, 1))));
	if(block_is_solid(back))
	{	
		struct AABB block_aabb = block_get_aabb(back->position);

		if(physics_aabbs_overlap(camera->aabb, block_aabb))
		{	
			camera->velocity.z = 0;
			camera->position.z = back->position.z + -1.0f;
		}			
	}

	struct Block *back2 = world_get_block(world, vec3_round(vec3_add(camera->position, vec3(0, 0, 1))));
	if(block_is_solid(back2))
	{	
		struct AABB block_aabb = block_get_aabb(back2->position);

		if(physics_aabbs_overlap(camera->aabb, block_aabb))
		{	
			camera->velocity.z = 0;
			camera->position.z = back2->position.z + -1.0f;
		}			
	}
}

bool physics_aabbs_overlap(struct AABB a, struct AABB b)
{
	return	(a.min.x <= b.max.x && a.max.x >= b.min.x) &&
         	(a.min.y <= b.max.y && a.max.y >= b.min.y) &&
         	(a.min.z <= b.max.z && a.max.z >= b.min.z);
}