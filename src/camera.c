#include "camera.h"
#include <math.h>

void camera_init(struct Camera *camera)
{
	camera->position = vec3(0,50,0);
    camera->rotation = vec3(0,0,0);
    camera->target = vec3(0,0,-1);
	camera->lastx = 600;
	camera->lasty = 400;
	camera->fov = 90.0f;
	camera->mass = 1.0f;
	camera->velocity = vec3(0,0,0);
	camera->force = vec3(0,0,0);
	camera->jumping = false;
	camera->free = false;
}

void camera_move(struct Camera *camera, struct Vec3 offset)
{	
	camera->position = vec3_add(camera->position, offset);
}

void camera_rotate(struct Camera *camera, float xpos, float ypos, float delta_time)
{   
	float *pitch = &camera->rotation.x;
	float *yaw = &camera->rotation.y;

	float xoffset = xpos - camera->lastx;
	float yoffset = camera->lasty - ypos;
	camera->lastx = xpos;
	camera->lasty = ypos;

	*yaw += xoffset * 0.1f;
	*pitch += yoffset * 0.1f;

	//Prevents the camera's yaw value from going over 360
	*yaw = fmod(*yaw, 360.0f);

	if(*pitch > 89.0f)
		*pitch = 89.0f;
	if(*pitch < -89.0f)
		*pitch = -89.0f;

	struct Vec3 direction = {
		.x = cos(radians(*yaw)) * cos(radians(*pitch)),
		.y = sin(radians(*pitch)),
		.z = sin(radians(*yaw)) * cos(radians(*pitch))
	};
	camera->target = vec3_normalize(direction);

	camera->right = vec3_normalize(vec3_cross(vec3(0,1,0), camera->target));
	camera->up = vec3_cross(camera->target, camera->right);
}

void camera_update_aabb(struct Camera *camera)
{
	camera->aabb.min = vec3_add(camera->position, vec3(-0.5f, -1.5f, -0.5f));
	camera->aabb.max = vec3_add(camera->position, vec3(0.5f, 0.5f, 0.5f));
}