#include <glfw3.h>
#include "libft.h"
#include "atari.h"
#include "ball.h"

void draw_rect(double largeur,double hauteur)
{
    glBegin(GL_QUADS);
    glVertex2d(0,-hauteur/2);
    glVertex2d(0,hauteur/2);
    glVertex2d(largeur,hauteur/2);
    glVertex2d(largeur,-hauteur/2);
    glEnd();
}

int main(int ac, char *av[])
{
    GLFWwindow	*window;
    t_level     levels[N_LEVELS];
	t_ball		ball;
	int			level_index;

	level_index = ac > 1 ? ft_atoi(av[1]) : 0;
	initGLFW(&window);
    load_levels(levels);
	initBall(&ball);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);
        //clear screen
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);

		renderer(window, levels, &ball, level_index);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
	}
	cleanGLFW(window);
    return (0);
}
