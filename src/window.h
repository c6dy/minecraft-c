#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

struct GLFWwindow* window_init(int width, int height, const char *title, void *game);
void window_swap_buffers(struct GLFWwindow *window);
void window_poll_events();
void window_close();

#endif