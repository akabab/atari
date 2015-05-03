#include "atari.h"

int				renderer(GLFWwindow *window, t_level *levels,
		t_ball *ball, int level_index)
{
	draw_level(&levels[level_index]);
	if (!update_ball(ball))
		/*if (!checkLives())
		  break*/ ;
		draw_ball(ball);
	return (1);
}
