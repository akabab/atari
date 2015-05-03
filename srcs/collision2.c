#include "atari.h"

int				check_tr_two(t_ball *ball, t_brick *brick)
{
	float		xb;
	float		yb;

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
	return (0);
}

int				check_tl_two(t_ball *ball, t_brick *brick)
{
	float		xb;
	float		yb;

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
	return (0);
}

int				check_bl_two(t_ball *ball, t_brick *brick)
{
	float		xb;
	float		yb;

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
	return (0);
}

int				check_br_two(t_ball *ball, t_brick *brick)
{
	float		xb;
	float		yb;

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
	return (0);
}
