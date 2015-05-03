#include "atari.h"

void	reset_viewport(GLFWwindow *window)
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

t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)ft_memalloc(sizeof(t_game));
	if (!game)
		exit(EXIT_FAILURE);
	load_levels(game->levels);
	return (game);
}

void	render(GLFWwindow *window, t_game *game)
{
	draw_level(game->levels[game->cur_level_index]);
}

int		main(int ac, char *av[])
{
	GLFWwindow	*window;
	t_game		*game;

	init_glfw(&window);
	game = init_game();
	game->cur_level_index = ac > 1 ? ft_atoi(av[1]) : 0; //

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		reset_viewport(window);
		glMatrixMode(GL_MODELVIEW);
		/* Render here */
		render(window, game);

		//Check collision

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}
	clean_glfw(window);
	return (0);
}
