#include "atari.h"
#include "ball.h"
#include <math.h>

// int					update_pad(t_pad *pad)
// {
// 	ball->x += ball->speed * cos(ball->rad);
// 	ball->y += ball->speed * sin(ball->rad);
// 	if (!check_bounds(ball))
// 		return (0);
// 	//checkCollisions(ball);
// 	return (1);
// }

t_pad				*init_pad(void)
{
	t_pad	*pad;

	pad = (t_pad *)ft_memalloc(sizeof(t_pad));
	if (!pad)
		exit(EXIT_FAILURE);
	pad->x0 = PAD_INIT_X;
	pad->y0 = PAD_INIT_Y;
	pad->x1 = PAD_INIT_WIDTH;
	pad->y1 = PAD_INIT_HEIGHT;
	pad->scale = PAD_INIT_SCALE;
	pad->speed = PAD_INIT_SPEED;
	return (pad);
}
