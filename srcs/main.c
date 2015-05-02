#include "atari.h"
#include "libft.h"
#include <glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include "ball.h"

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

/* received new win size after resize */
void window_size_callback(GLFWwindow* window, int width, int height)
{
    // ft_printf("resize-> width: %d, height: %d\n", width, height);
}

int main(int ac, char *av[])
{
    t_level     levels[N_LEVELS];

    load_levels(levels);

    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    /* Initialize the library */
    if (!glfwInit())
        exit(EXIT_FAILURE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Atari", NULL, NULL); //glfwGetPrimaryMonitor(), NULL); for full screen
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* notified when a window is resized */
    glfwSetWindowSizeCallback(window, window_size_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Set interval for buffer swapping */
    glfwSwapInterval(1);

    /* */
    glfwSetKeyCallback(window, key_callback);

	t_ball ball;
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

        // glMatrixMode(GL_PROJECTION);
        // glLoadIdentity();
        // glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        // glMatrixMode(GL_MODELVIEW);

        // glLoadIdentity();
        // glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

		//
        int level_index;
        if (ac > 1)
            level_index = ac > 1 ? ft_atoi(av[1]) : 0;
		draw_level(&levels[level_index]);
		if (!updateBall(&ball))
			break ;
		drawBall(&ball);

        //draw triangle
		/*glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();*/

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    /* clear all and exit */
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

    return (0);
}
