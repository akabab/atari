#include <glfw3.h>
#include "libft.h"
#include "atari.h"
#include "ball.h"

#include <unistd.h>

int				main(int ac, char *av[])
{
    GLFWwindow	*window;
    t_level     levels[N_LEVELS];
	t_ball		ball;
	int			level_index;

	level_index = ac > 2 ? ft_atoi(av[1]) : 0;
	initGLFW(&window);
    load_levels(levels);
	initBall(&ball);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
		renderer(window, levels, &ball, level_index);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
	}
	cleanGLFW(window);
    return (0);
}
