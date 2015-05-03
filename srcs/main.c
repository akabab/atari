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

int		main(int ac, char *av[])
{
	GLFWwindow	*window;
	t_level		levels[N_LEVELS];
	t_ball		ball;
	int			level_index;

	level_index = ac > 1 ? ft_atoi(av[1]) : 0;
	init_glfw(&window);
	load_levels(levels);
	init_ball(&ball);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		reset_viewport(window);
		glMatrixMode(GL_MODELVIEW);
		/* Render here */
		renderer(window, levels, &ball, level_index);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}
	clean_glfw(window);
	return (0);
}
