#include "atari.h"

static int				check_pad(t_ball *ball, t_pad *pad)
{
	float			xb;
	float			yb;

	xb = ball->x;
	yb = ball->y - ball->r;
	if (xb >= P(x0) && xb <= P(x1) &&
			yb >= P(y0) && yb <= P(y1))
	{
		if (xb < (P(x1) - P(x0)) / 4)
			ball->speedx = -0.06;
		else if (xb < ((P(x1) - P(x0)) * 2) / 4)
			ball->speedx = -0.018;
		else if (xb < ((P(x1) - P(x0)) * 3) / 4)
			ball->speedx = 0.018;
		else if (xb < (P(x1) - P(x0)))
			ball->speedx = 0.06;;
		ball->speedy = -ball->speedy;
		ball->y += ball->r;
		return (1);
	}
	return (0);
}

void					update_pad(t_pad *pad, t_ball *ball)
{
	t_game		*game;
	t_keys		*keys;

	game = get_game();
	keys = game->keys;
	if (keys->right == TRUE && (pad->x1 + pad->speed < E_X - LEVEL_MARGIN))
	{
		pad->x0 += pad->speed;
		pad->x1 += pad->speed;
	}
	if (keys->left == TRUE && (pad->x0 - pad->speed > W_X + LEVEL_MARGIN))
	{
		pad->x0 -= pad->speed;
		pad->x1 -= pad->speed;
	}
	check_pad(ball, pad);
}

t_pad				*init_pad(void)
{
	t_pad	*pad;

	pad = (t_pad *)ft_memalloc(sizeof(t_pad));
	if (!pad)
		exit(EXIT_FAILURE);
	pad->x0 = PAD_INIT_X - PAD_INIT_WIDTH / 2;
	pad->y1 = PAD_INIT_Y - PAD_INIT_HEIGHT / 2;
	pad->x1 = PAD_INIT_X + PAD_INIT_WIDTH / 2;
	pad->y0 = PAD_INIT_Y + PAD_INIT_HEIGHT / 2;
	pad->scale = PAD_INIT_SCALE;
	pad->speed = PAD_INIT_SPEED;
	return (pad);
}
