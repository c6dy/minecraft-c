#ifndef GAME_H
#define GAME_H

#include "window.h"
#include "renderer.h"
#include "camera.h"
#include "world.h"

struct Game
{   
    struct GLFWwindow *window;
    struct Renderer renderer;
    struct Camera camera;
	struct World world;
    float last_frame, delta_time;
};

void game_init(struct Game *game);
void game_run(struct Game *game);
void game_calculate_delta_time(struct Game *game);
void game_shutdown();

#endif