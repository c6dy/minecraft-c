#include <glad/glad.h>
#include "window.h"
#include "input.h"

struct GLFWwindow* window_init(int width, int height, const char *title, void *game)
{   
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    struct GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);

    glfwMakeContextCurrent(window);
    gladLoadGL();

	//glfwSwapInterval(0);

	glfwSetWindowUserPointer(window, game);
	glfwSetMouseButtonCallback(window, input_handle_mouse_buttons);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Get size of monitor and set the window to the middle of the screen
	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    glfwSetWindowPos(window, (mode->width - width) / 2, (mode->height - height) / 2);

	return window;
}

void window_swap_buffers(struct GLFWwindow *window)
{
    glfwSwapBuffers(window);
}

void window_poll_events()
{
    glfwPollEvents();
}

void window_close()
{
    glfwTerminate();
}