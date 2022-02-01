#ifndef PHYSICS_H
#define PHYSICS_H

#include "math/core.h"
#include "camera.h"
#include "world.h"
#include "aabb.h"
#include <stdbool.h>

#define GRAVITY vec3(0, -9.81, 0)
#define PHYSICS_TIMESTEP 0.016f

void physics_simulate(struct World *world, void *rb, float delta_time);
void physics_check_aabbs(struct World *world, struct Camera *camera);
bool physics_aabbs_overlap(struct AABB a, struct AABB b);

#endif