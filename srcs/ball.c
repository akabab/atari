#include "atari.h"

static t_bool		is_ball_outside(t_ball *ball)
{
	if ((ball->y - ball->r) <= BALL_OUT_LIMIT)
		return (TRUE);
	return (FALSE);
}

void				handle_bounds(t_ball *ball)
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
	if (INVINCIBLE_MODE && (ball->y - ball->r) <= -1.0f)
	{
		ball->speedy = -ball->speedy;
		ball->y = -1.0f + LEVEL_MARGIN + ball->r;
	}
}

static void			reset_ball(t_ball *ball)
{
	ball->x = BALL_ORIGIN_X;
	ball->y = BALL_ORIGIN_Y;
	ball->r = BALL_RADIUS;
	ball->speedx = BALL_ORIGIN_SPEEDX;
	ball->speedy = BALL_ORIGIN_SPEEDY;
}

void				update_ball(t_ball *ball, t_list_node *bricks)
{
	int				i;
	t_game			*game;

	game = get_game();
	i = 0;
	while (i < 10)
	{
		ball->x += (ball->speedx) / 10.0f;
		ball->y += (ball->speedy) / 10.0f;
		handle_bounds(ball);
		if (!INVINCIBLE_MODE && is_ball_outside(ball))
		{
			game->cur_level->lives--;
			reset_ball(ball);
		}
		check_collisions(ball, bricks);
		i++;
	}
}

t_ball				*init_ball(void)
{
	t_ball	*ball;

	ball = (t_ball *)ft_memalloc(sizeof(t_ball));
	if (!ball)
		exit(EXIT_FAILURE);
	reset_ball(ball);
	return (ball);
}
