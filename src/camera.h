#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include "math/core.h"
#include "aabb.h"
#include <stdbool.h>

struct Camera
{
    struct Vec3 position, rotation, target, right, up;
    float lastx, lasty;
	struct Mat4 view_matrix, projection_matrix;
	float fov;

	struct AABB aabb;
	struct Vec3 velocity, force;
	float mass;
	bool jumping, free;
};

void camera_init(struct Camera *camera);
void camera_move(struct Camera *camera, struct Vec3 offset);
void camera_rotate(struct Camera *camera, float xpos, float ypos, float delta_time);
void camera_update_aabb(struct Camera *camera);

#endif