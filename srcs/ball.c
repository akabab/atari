#include "atari.h"

int					update_ball(t_ball *ball, t_list_node *bricks)
{
	ball->x += ball->speed * cos(ball->rad);
	ball->y += ball->speed * sin(ball->rad);
	if (!check_bounds(ball))
		return (0);
	check_collisions(ball, bricks);
	return (1);
}

int					check_bounds(t_ball *ball)
{
	if ((ball->x + ball->r) >= (1.0f - LEVEL_MARGIN))
	{
		ball->rad = fmod((M_PI - ball->rad), (2.0f * M_PI));
		ball->x = 1.0f - LEVEL_MARGIN - ball->r;
	}
	if ((ball->x - ball->r) <= (-1.0f + LEVEL_MARGIN))
	{
		ball->rad = fmod((M_PI - ball->rad), (2.0f * M_PI));
		ball->x = -1.0f + LEVEL_MARGIN + ball->r;
	}
	if ((ball->y + ball->r) >= (1.0f - LEVEL_MARGIN))
	{
		ball->rad = (ball->rad) * -1;
		ball->y = 1.0f - LEVEL_MARGIN - ball->r;
	}
	if ((ball->y - ball->r) <= (-1.0f + LEVEL_MARGIN))
		ball->rad = (ball->rad) * -1;
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
	ball->speed = BALL_ORIGIN_SPEED;
	ball->rad = BALL_MVT_ANGLE;
	return (ball);
}
