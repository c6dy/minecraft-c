#include "game.h"
#include "input.h"
#include <stdlib.h>
#include "physics.h"

void game_init(struct Game *game)
{
	game->window = window_init(1200, 800, "Minecraft", game);
	renderer_init(&game->renderer);
	camera_init(&game->camera);
	world_init(&game->world);
	game->delta_time = 0;
}

void game_run(struct Game *game)
{	
	while (!glfwWindowShouldClose(game->window))
	{
		game_calculate_delta_time(game);
		
		renderer_clear();

		input_handle(game);
		
		world_resize(&game->world, vec2(game->camera.position.x, game->camera.position.z));
			
		for (int i = 0; i < game->world.chunk_count; i++)
		{	
			if(game->world.chunks[i].visible)
				renderer_draw_chunk(&game->renderer, &game->world.chunks[i]);
		}

		if(game->world.loaded)
     		physics_simulate(&game->world, &game->camera, game->delta_time);

		window_swap_buffers(game->window);
		window_poll_events(game->window);

		//printf("%f\n", game->delta_time);
	}
}

void game_calculate_delta_time(struct Game *game)
{
	float current_frame = glfwGetTime();
	game->delta_time = current_frame - game->last_frame;
	game->last_frame = current_frame;
}

void game_shutdown(struct Game *game)
{
	free(game->world.chunks);
	window_close();
}