#include "atari.h"

static void			error_callback(int error, const char *description)
{
	ft_putstr_fd(description, 2);
}

static void			key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	t_game		*game;
	t_keys		*keys;
	t_pad		*pad;

	game = get_game();
	keys = game->keys;
	pad = game->levels[game->cur_level_index]->pad;
	handle_arrow_keys(keys, key, action);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		load_level(game, 2);
	// if (action == GLFW_REPEAT)
	//     printf("repeat\n");
	// if (action == GLFW_PRESS)
	//     printf("press\n");
	// if (action == GLFW_RELEASE)
	//     printf("release\n");

	// if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	// {
	// 	pad->x0 = pad->x0 - (PAD_INIT_WIDTH * pad->scale) / 2;
	// 	pad->x1 = pad->x1 + (PAD_INIT_WIDTH * pad->scale) / 2;
	// }
}

/* received new win size after resize */
static void			window_size_callback(GLFWwindow *window, int width, int height)
{
	// ft_printf("resize-> width: %d, height: %d\n", width, height);
}

int					init_glfw(GLFWwindow **window)
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

int					clean_glfw(GLFWwindow *window)
{
	/* clear all before end */
	glfwDestroyWindow(window);
	glfwTerminate();
	return (1);
}
