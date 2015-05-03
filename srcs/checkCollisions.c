#include <math.h>
#include "list.h"
#include "atari.h"
#include "ball.h"

#define B(X) brick->X

static int			checkTopR(t_ball *ball, t_brick *brick)
{
	float			xb;
	float			yb;

	if (ball->rad >= 0 && ball->rad <= (M_PI / 2))
	{
		xb = ball->x;
		yb = ball->y + ball->r;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
			rebound(ball, brick, 1);
		xb = ball->x + ball->r;
		yb = ball->y;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
			rebound(ball, brick, 2);
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
		}
		return (1);
	}
	return (0);
}

static int			checkTopL(t_ball *ball, t_brick *brick)
{
	float			xb;
	float			yb;

	if (ball->rad > (M_PI / 2)  && ball->rad <= M_PI)
	{
		xb = ball->x;
		yb = ball->y + ball->r;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
			rebound(ball, brick, 1);
		xb = ball->x - ball->r;
		yb = ball->y;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
			rebound(ball, brick, 4);
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
		}
		return (1);
	}
	return (0);
}

static int			checkBotL(t_ball *ball, t_brick *brick)
{
	float			xb;
	float			yb;

	if (ball->rad > (M_PI)  && ball->rad <= (3 * M_PI) / 2)
	{
		xb = ball->x;
		yb = ball->y - ball->r;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
			rebound(ball, brick, 3);
		xb = ball->x - ball->r;
		yb = ball->y;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
			rebound(ball, brick, 4);
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
		}
		return (1);
	}
	return (0);
}

static int			checkBotR(t_ball *ball, t_brick *brick)
{
	float			xb;
	float			yb;

	if (ball->rad > (3 * M_PI) / 2 && ball->rad < (2 * M_PI))
	{
		xb = ball->x;
		yb = ball->y - ball->r;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
			rebound(ball, brick, 3);
		xb = ball->x + ball->r;
		yb = ball->y;
		if (xb >= B(x0) && xb <= B(x1) &&
				yb >= B(y0) && yb <= B(y1))
			rebound(ball, brick, 4);
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
		}
		return (1);
	}
	return (0);
}

int					checkCollisions(t_ball *ball, t_list_node **bricks)
{
	t_list_node		*current;
	t_brick			*cur_brick;

	current = *bricks;
	while (current != NULL)
	{
		cur_brick = (t_brick *)current->value;
		if (cur_brick->val &&
				(checkTopR(ball, cur_brick) ||
				 checkTopL(ball, cur_brick) ||
				 checkBotR(ball, cur_brick) ||
				 checkBotL(ball, cur_brick)))
		{
			if (cur_brick->val && cur_brick->val != STATIC_BLOCK)
				cur_brick->val--;
			break ;
		}
		current = current->next;
	}
	return (1);
}
