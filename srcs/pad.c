#include "atari.h"

void					update_pad(t_pad *pad)
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
	if (keys->up == TRUE)
		pad->scale += 0.001f;
	if (keys->down == TRUE)
		pad->scale -= 0.001f;
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
