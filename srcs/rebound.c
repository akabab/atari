#include <math.h>
#include "atari.h"
#include "ball.h"

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
	return (1);
}
