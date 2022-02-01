#include "input.h"
#include <math.h>
#include "math/core.h"

void input_handle(struct Game *game)
{	
	input_handle_cursor(game);	
	input_handle_keys(game);
}

void input_handle_cursor(struct Game *game)
{
	double xpos, ypos;
	glfwGetCursorPos(game->window, &xpos, &ypos);

	camera_rotate(&game->camera, xpos, ypos, game->delta_time);

	// Calculate view and projection matrices
	game->camera.view_matrix = lookat(game->camera.position, vec3_add(game->camera.position, game->camera.target), vec3(0, 1, 0));
	game->camera.projection_matrix = perspective(game->camera.fov, 1200.0f/800.0f, 0.1f, 500.0f);

	// Update uniform values
	renderer_use_shader(&game->renderer, SHADER_BLOCK);
	shader_set_mat4(game->renderer.shader, "v", &game->camera.view_matrix);
	shader_set_mat4(game->renderer.shader, "p", &game->camera.projection_matrix);
	shader_set_vec3(game->renderer.shader, "camera_position", &game->camera.position);
}

void input_handle_keys(struct Game *game)
{	
	if (glfwGetKey(game->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(game->window, 1);
	if (glfwGetKey(game->window, GLFW_KEY_COMMA) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(game->window, GLFW_KEY_PERIOD) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(game->window, GLFW_KEY_9) == GLFW_PRESS)
		game->camera.free = true;
	if (glfwGetKey(game->window, GLFW_KEY_0) == GLFW_PRESS)
		game->camera.free = false;

	if(glfwGetKey(game->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if(game->camera.free)
			camera_move(&game->camera, vec3_scale(game->camera.target, 0.3));
		else {	
			game->camera.force.x += game->camera.target.x * 30;
			game->camera.force.z += game->camera.target.z * 30;
		}
	}

	if(glfwGetKey(game->window, GLFW_KEY_S) == GLFW_PRESS)
	{	
		if(game->camera.free)
			camera_move(&game->camera, vec3_scale(vec3_inverse(game->camera.target), 0.3));
		else {
			game->camera.force.x += -game->camera.target.x * 30;
			game->camera.force.z += -game->camera.target.z * 30;
		}
	}

	if(glfwGetKey(game->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if(game->camera.free)
			camera_move(&game->camera, vec3_scale(vec3_inverse(vec3_normalize(vec3_cross(game->camera.target, game->camera.up))), 0.3));
		else {
			game->camera.force = vec3_add(game->camera.force,vec3_scale(vec3_inverse(vec3_normalize(vec3_cross(game->camera.target, game->camera.up))), 20));
		}
	}

	if(glfwGetKey(game->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if(game->camera.free)
			camera_move(&game->camera, vec3_scale(vec3_normalize(vec3_cross(game->camera.target, game->camera.up)), 0.3));
		else {
			game->camera.force = vec3_add(game->camera.force,vec3_scale(vec3_normalize(vec3_cross(game->camera.target, game->camera.up)), 20));
		}
	}
	
	if(glfwGetKey(game->window, GLFW_KEY_SPACE) == GLFW_PRESS && !game->camera.jumping)
	{
		game->camera.force = vec3_add(game->camera.force, vec3(0, 300, 0));
		game->camera.jumping = true;
	}

	if (glfwGetKey(game->window, GLFW_KEY_1) == GLFW_PRESS)
		game->world.selected_block = BLOCK_GRASS;
	if (glfwGetKey(game->window, GLFW_KEY_2) == GLFW_PRESS)
		game->world.selected_block = BLOCK_SAND;
	if (glfwGetKey(game->window, GLFW_KEY_3) == GLFW_PRESS)
		game->world.selected_block = BLOCK_DIRT;
	if (glfwGetKey(game->window, GLFW_KEY_4) == GLFW_PRESS)
		game->world.selected_block = BLOCK_WOOD;
	if (glfwGetKey(game->window, GLFW_KEY_5) == GLFW_PRESS)
		game->world.selected_block = BLOCK_STONE;
	if (glfwGetKey(game->window, GLFW_KEY_6) == GLFW_PRESS)
		game->world.selected_block = BLOCK_TREE;
}

void input_handle_mouse_buttons(GLFWwindow* window, int button, int action, int mods)
{
	struct Game *game = glfwGetWindowUserPointer(window);

	if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)	
		world_remove_block(&game->world, &game->camera, BLOCK_AIR);

	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		world_place_block(&game->world, &game->camera, game->world.selected_block);
}