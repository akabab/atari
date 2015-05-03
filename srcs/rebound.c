#include "atari.h"

int					rebound(t_ball *ball, t_brick *brick, int side)
{
	float			tab[5];
	float			tmp;

	tmp = ball->rad;
	tab[0] = fmod((tmp + M_PI), (2 * M_PI));
	tab[1] = tmp * -1;
	tab[2] = fmod((M_PI - tmp), (2 * M_PI));
	tab[3] = tmp * -1;
	tab[4] = fmod((M_PI - tmp), (2 * M_PI));
	ball->rad = tab[side];
	if (brick->val != STATIC_BRICK)
		brick->val--;
	return (1);
}
