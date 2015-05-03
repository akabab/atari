#include "atari.h"

static int		check_top_right(t_ball *ball, t_brick *brick)
{
	float			xb;
	float			yb;

	if (ball->speedx >= 0 && ball->speedy >=0)
	{
		xb = ball->x;
		yb = ball->y + ball->r;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			rebound(ball, brick, 1);
			ball->y -= ball->r;
			return (1);
		}
		xb = ball->x + ball->r;
		yb = ball->y;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			rebound(ball, brick, 2);
			ball->x -= ball->r;
			return (1);
		}
		xb = ball->x + ((SQRT_2 / 2) * ball->r);
		yb = ball->y + ((SQRT_2 / 2) * ball->r);
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			if (xb - B(x0) >= yb - B(y0))
			{
				rebound(ball, brick, 1);
				ball->y -= ((SQRT_2 / 2) * ball->r);
			}
			else
			{
				rebound(ball, brick, 2);
				ball->x -= ((SQRT_2 / 2) * ball->r);
			}
			return (1);
		}
	}
	return (0);
}

static int		check_top_left(t_ball *ball, t_brick *brick)
{
	float			xb;
	float			yb;

	if (ball->speedx < 0  && ball->speedy >= 0)
	{
		xb = ball->x;
		yb = ball->y + ball->r;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			rebound(ball, brick, 1);
			ball->y -= ball->r;
			return (1);
		}
		xb = ball->x - ball->r;
		yb = ball->y;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			rebound(ball, brick, 4);
			ball->x += ball->r;
			return (1);
		}
		xb = ball->x - ((SQRT_2 / 2) * ball->r);
		yb = ball->y + ((SQRT_2 / 2) * ball->r);
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			if (B(x1) - xb >= yb - B(y0))
			{
				rebound(ball, brick, 1);
				ball->y -= (SQRT_2 / 2 * ball->r);
			}
			else
			{
				rebound(ball, brick, 4);
				ball->x += (SQRT_2 / 2 * ball->r);
			}
			return (1);
		}
	}
	return (0);
}

static int		check_bottom_left(t_ball *ball, t_brick *brick)
{
	float			xb;
	float			yb;

	if (ball->speedx < 0 && ball->speedy < 0)
	{
		xb = ball->x;
		yb = ball->y - ball->r;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			rebound(ball, brick, 3);
			ball->y += ball->r;
			return (1);
		}
		xb = ball->x - ball->r;
		yb = ball->y;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			rebound(ball, brick, 4);
			ball->x += ball->r;
			return (1);
		}
		xb = ball->x - ((SQRT_2 / 2) * ball->r);
		yb = ball->y - ((SQRT_2 / 2) * ball->r);
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			if (B(x1) - xb >= B(y1) - yb)
			{
				rebound(ball, brick, 3);
				ball->y += (SQRT_2 / 2 * ball->r);
			}
			else
			{
				rebound(ball, brick, 4);
				ball->x += (SQRT_2 / 2 * ball->r);
			}
			return (1);
		}
	}
	return (0);
}

static int		check_bottom_right(t_ball *ball, t_brick *brick)
{
	float			xb;
	float			yb;

	if (ball->speedx >= 0 && ball->speedy < 0)
	{
		xb = ball->x;
		yb = ball->y - ball->r;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			rebound(ball, brick, 2);
			ball->y -= ball->r;
			return (1);
		}
		xb = ball->x + ball->r;
		yb = ball->y;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			rebound(ball, brick, 3);
			ball->x -= ball->r;
			return (1);
		}
		xb = ball->x + ((SQRT_2 / 2) * ball->r);
		yb = ball->y - ((SQRT_2 / 2) * ball->r);
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			if (xb - B(x0) >= B(y1) - yb)
			{
				rebound(ball, brick, 2);
				ball->x -= (SQRT_2 / 2 * ball->r);
			}
			else
			{
				rebound(ball, brick, 3);
				ball->y += (SQRT_2 / 2 * ball->r);
			}
			return (1);
		}
	}
	return (0);
}

int				check_collisions(t_ball *ball, t_list_node *bricks)
{
	t_list_node		*cursor;
	t_brick			*cur_brick;

	cursor = bricks;
	while (cursor != NULL)
	{
		cur_brick = (t_brick *)cursor->value;
		if (cur_brick->val > 0 &&
				(check_top_right(ball, cur_brick) ||
				 check_top_left(ball, cur_brick) ||
				 check_bottom_right(ball, cur_brick) ||
				 check_bottom_left(ball, cur_brick)))
		{
			cursor = bricks;
			continue ;
		}
		cursor = cursor->next;
	}
	return (1);
}

