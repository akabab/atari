#include "atari.h"

void            draw_ball(float pos_x, float pos_y)
{
    float           x;
    float           y;
    int             i;

    glBegin(GL_POLYGON);
    glColor3ub(PINK);
    i = 0;
    while (i < 20)
    {
        x = pos_x + 0.02f * (cos(i * 2.0f * M_PI / 20.0f));
        y = pos_y + 0.02f * (sin(i * 2.0f * M_PI / 20.0f));
        glVertex2f(x, y);
        i++;
    }
    glEnd();
}

void    draw_life(void)
{
    draw_ball(0.0f, 0.0f);
    draw_ball(0.04f, 0.0f);
    glBegin(GL_TRIANGLES);
        glColor3ub(PINK);
        glVertex3f(0.02f, -0.06f, 0);
        glVertex3f(0.061f, 0.0f, 0);
        glVertex3f(-0.022f, 0.0f, 0);
    glEnd();
}

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

void		free_all()
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

t_game		*get_game(void)
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

void	render(GLFWwindow *window, t_game *game)
{
	draw_level(game->levels[game->cur_level_index]);
}

int		main(int ac, char *av[])
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
		render(window, game);

		draw_life();

		//Check collision

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}
	clean_glfw(window);
	return (0);
}
