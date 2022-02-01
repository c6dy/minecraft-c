#ifndef INPUT_H
#define INPUT_H

#include "game.h"

void input_handle(struct Game *game);
void input_handle_cursor(struct Game *game);
void input_handle_keys(struct Game *game);
void input_handle_mouse_buttons(struct GLFWwindow *window, int button, int action, int mods);

#endif