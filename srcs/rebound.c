#include "atari.h"

int					rebound(t_ball *ball, t_brick *brick, int side)
{
	if (brick->val != 9)
		brick->val--;
	if (side == 1 || side == 3)
		ball->speedy = -ball->speedy;
	if (side == 2 || side == 4)
		ball->speedx = -ball->speedx;
	return (1);
}
