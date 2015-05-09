#include "atari.h"

int					rebound(t_ball *ball, t_brick *brick, int side)
{
	t_game		*game;
	t_level		*cur_level;

	game = get_game();
	cur_level = game->cur_level;
	if (brick->val != STATIC_BRICK)
	{
		cur_level->score += brick->val;
		brick->val--;
		if (brick->val == 0)
			cur_level->active_bricks -= 1;
	}
	if (side == 1 || side == 3)
		ball->speedy = -ball->speedy;
	if (side == 2 || side == 4)
		ball->speedx = -ball->speedx;
	return (1);
}
