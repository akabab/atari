#include "atari.h"

static int		check_top_right(t_ball *ball, t_brick *brick)
{
	float			xb;
	float			yb;

	if (ball->rad >= 0 && ball->rad <= (M_PI / 2))
	{
		xb = ball->x;
		yb = ball->y + ball->r;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			rebound(ball, brick, 1);
			return (1);
		}
		xb = ball->x + ball->r;
		yb = ball->y;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			rebound(ball, brick, 2);
			return (1);
		}
		xb = ball->x + ((sqrt(2) / 2) * ball->r);
		yb = ball->y + ((sqrt(2) / 2) * ball->r);
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			if (xb - B(x0) > yb - B(y0))
				rebound(ball, brick, 1);
			else if (xb - B(x0) < yb - B(y0))
				rebound(ball, brick, 2);
			else
				rebound(ball, brick, 0);
			return (1);
		}
	}
	return (0);
}

static int		check_top_left(t_ball *ball, t_brick *brick)
{
	float			xb;
	float			yb;

	if (ball->rad > (M_PI / 2)  && ball->rad <= M_PI)
	{
		xb = ball->x;
		yb = ball->y + ball->r;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			rebound(ball, brick, 1);
			return (1);
		}
		xb = ball->x - ball->r;
		yb = ball->y;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			rebound(ball, brick, 4);
			return (1);
		}
		xb = ball->x - ((sqrt(2) / 2) * ball->r);
		yb = ball->y + ((sqrt(2) / 2) * ball->r);
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			if (B(x1) - xb > yb - B(y0))
				rebound(ball, brick, 1);
			else if (B(x1) - xb < yb - B(y0))
				rebound(ball, brick, 4);
			else
				rebound(ball, brick, 0);
			return (1);
		}
	}
	return (0);
}

static int		check_bottom_left(t_ball *ball, t_brick *brick)
{
	float			xb;
	float			yb;

	if (ball->rad > (M_PI)  && ball->rad <= (3 * M_PI) / 2)
	{
		xb = ball->x;
		yb = ball->y - ball->r;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			rebound(ball, brick, 3);
			return (1);
		}
		xb = ball->x - ball->r;
		yb = ball->y;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			rebound(ball, brick, 4);
			return (1);
		}
		xb = ball->x - ((sqrt(2) / 2) * ball->r);
		yb = ball->y - ((sqrt(2) / 2) * ball->r);
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			if (B(x1) - xb > B(y1) - yb)
				rebound(ball, brick, 3);
			else if (B(x1) - xb < B(y1) - yb)
				rebound(ball, brick, 4);
			else
				rebound(ball, brick, 0);
			return (1);
		}
	}
	return (0);
}

static int		check_bottom_right(t_ball *ball, t_brick *brick)
{
	float			xb;
	float			yb;

	if (ball->rad > (3 * M_PI) / 2 && ball->rad < (2 * M_PI))
	{
		xb = ball->x;
		yb = ball->y - ball->r;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			rebound(ball, brick, 2);
			return (1);
		}
		xb = ball->x + ball->r;
		yb = ball->y;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			rebound(ball, brick, 3);
			return (1);
		}
		xb = ball->x + ((sqrt(2) / 2) * ball->r);
		yb = ball->y - ((sqrt(2) / 2) * ball->r);
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
		{
			if (xb - B(x0) > B(y1) - yb)
				rebound(ball, brick, 2);
			else if (xb - B(x0) < B(y1) - yb)
				rebound(ball, brick, 3);
			else
				rebound(ball, brick, 0);
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

