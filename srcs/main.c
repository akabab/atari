#include "atari.h"

void			reset_viewport(GLFWwindow *window)
{
	float	ratio;
	int		width;
	int		height;

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
}

void			free_all(void)
{
	t_game		*game;

	game = get_game();
	if (!game)
		exit(EXIT_FAILURE);
	//free game->levels[]
	//	- free(level->pad);
	//	- free(level->ball);
	//	- list_clear_destroy(level->brick_list);
	free(game);
}

t_game			*get_game(void)
{
	static t_game	*game = NULL;

	if (!game)
	{
		game = (t_game *)ft_memalloc(sizeof(t_game));
		if (!game)
			exit(EXIT_FAILURE);
		load_levels(game->levels);
		game->keys = init_keys();
	}
	return (game);
}

static void		render(t_game *game)
{
	draw_level(game->levels[game->cur_level_index]);
}

int				main(int ac, char *av[])
{
	GLFWwindow	*window;
	t_game		*game;

	init_glfw(&window);
	game = get_game();
	load_level(game, ac > 1 ? ft_atoi(av[1]) : 0);
	while (!glfwWindowShouldClose(window))
	{
		handle_levels(game);
		reset_viewport(window);
		glMatrixMode(GL_MODELVIEW);
		/* Render here */
		render(game);
		//Check collision
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	clean_glfw(window);
	return (0);
}
