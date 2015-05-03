#include "atari.h"

int					update_ball(t_ball *ball, t_list_node *bricks)
{
	int				i;

	i = 0;
	while (i < 10)
	{

		ball->x += (ball->speedx) / 10.0f;
		ball->y += (ball->speedy) / 10.0f;
		if (!check_bounds(ball))
			return (0);
		check_collisions(ball, bricks);
		i++;
	}
	return (1);
}

int					check_bounds(t_ball *ball)
{
	if ((ball->x + ball->r) >= (1.0f - LEVEL_MARGIN))
	{
		ball->speedx = -ball->speedx;
		ball->x = 1.0f - LEVEL_MARGIN - ball->r;
	}
	if ((ball->x - ball->r) <= (-1.0f + LEVEL_MARGIN))
	{
		ball->speedx = -ball->speedx;
		ball->x = -1.0f + LEVEL_MARGIN + ball->r;
	}
	if ((ball->y + ball->r) >= (1.0f - LEVEL_MARGIN))
	{
		ball->speedy = -ball->speedy;
		ball->y = 1.0f - LEVEL_MARGIN - ball->r;
	}
	if ((ball->y - ball->r) <= (-1.0f + LEVEL_MARGIN))
		ball->speedy = -ball->speedy;
	//if (ball->y <= -1.0f)
	//	return (0);
	return (1);
}

t_ball				*init_ball(void)
{
	t_ball	*ball;

	ball = (t_ball *)ft_memalloc(sizeof(t_ball));
	if (!ball)
		exit(EXIT_FAILURE);
	ball->x = BALL_ORIGIN_X;
	ball->y = BALL_ORIGIN_Y;
	ball->r = BALL_RADIUS;
	ball->speedx = BALL_ORIGIN_SPEEDX;
	ball->speedy = BALL_ORIGIN_SPEEDY;
	return (ball);
}
