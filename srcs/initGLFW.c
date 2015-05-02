#include <glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "atari.h"

static void			error_callback(int error, const char *description)
{
	ft_putstr_fd(description, 2);
}

static void			key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

/* received new win size after resize */
void				window_size_callback(GLFWwindow *window, int width, int height)
{
    // ft_printf("resize-> width: %d, height: %d\n", width, height);
}

int					initGLFW(GLFWwindow **window)
{
    glfwSetErrorCallback(error_callback);
    /* Initialize the library */
    if (!glfwInit())
        exit(EXIT_FAILURE);
    /* Create a windowed mode window and its OpenGL context */
    *window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Atari", NULL, NULL); //glfwGetPrimaryMonitor(), NULL); for full screen
    if (!*window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    /* notified when a window is resized */
    glfwSetWindowSizeCallback(*window, window_size_callback);
    /* Make the window's context current */
    glfwMakeContextCurrent(*window);
    /* Set interval for buffer swapping */
    glfwSwapInterval(1);
    /* */
    glfwSetKeyCallback(*window, key_callback);
	return (1);
}

int					cleanGLFW(GLFWwindow *window)
{
    /* clear all before end */
    glfwDestroyWindow(window);
    glfwTerminate();
	return (1);
}
