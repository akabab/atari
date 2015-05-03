#include <math.h>
#include "libft.h"
#include "atari.h"
#include "ball.h"

int					checkCollisions(t_ball *ball, t_list **bricks)
{
	t_list			*current;

	current = *bricks;
	while (current->next != NULL)
	{
		if (checkTopR(ball, current->value) ||
				checkTopL(ball, current->value) ||
				checkBotR(ball, current->value) ||
				checkBotL(ball, current->value))
			break ;
		current = current->next;
	}
	return (1);
}

int					checkTopR(t_ball *ball, t_brick *brick)
{
	if (ball->rad >= 0 && ball->rad <= (M_PI / 2))
	{
		if (ball->x + ball->r >= brick->x0 &&
				ball->x + ball->r <= brick->x1 &&
				ball->y + ball->r >= brick->x0 &&
				ball->y + ball->r <= brick->y0)
		{
			rebound(ball, brick, 1);
			return (1);
		}
	}
	return (0);
}

int					checkTopL(t_ball *ball, t_brick *brick)
{
	if (ball->rad > (M_PI / 2)  && ball->rad <= M_PI)
	{
		if (ball->x + ball->r >= brick->x0 &&
				ball->x + ball->r <= brick->x1 &&
				ball->y + ball->r >= brick->x1 &&
				ball->y + ball->r <= brick->y1)
		{
			rebound(ball, brick, 2);
			return (1);
		}
	}
	return (0);
}

int					checkBotL(t_ball *ball, t_brick *brick)
{
	if (ball->rad > (M_PI)  && ball->rad <= (3 * M_PI) / 2)
	{
		if (ball->x + ball->r >= brick->y0 &&
				ball->x + ball->r <= brick->y1 &&
				ball->y + ball->r >= brick->x1 &&
				ball->y + ball->r <= brick->y1)
		{
			rebound(ball, brick, 3);
			return (1);
		}
	}
	return (0);
}

int					checkBotR(t_ball *ball, t_brick *brick)
{
	if (ball->rad > (3 * M_PI) / 2 && ball->rad < (2 * M_PI))
	{
		if (ball->x + ball->r >= brick->x0 &&
				ball->x + ball->r <= brick->y0 &&
				ball->y + ball->r >= brick->y0 &&
				ball->y + ball->r <= brick->y1)
		{
			rebound(ball, brick, 4);
			return (1);
		}
	}
	return (0);
}
