#include <glfw3.h>
#include "atari.h"
#include "ball.h"

int				renderer(GLFWwindow *window, t_level *levels,
		t_ball *ball, int level_index)
{
	float		ratio;
	int			width;
	int			height;

	/* Render here */
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float) height;
	glViewport(0, 0, width, height);
	//clear screen
	glClear(GL_COLOR_BUFFER_BIT);
	draw_level(&levels[level_index]);
	if (!updateBall(ball))
		/*if (!checkLives())
		  break*/ ;
	drawBall(ball);
	return (1);
}
