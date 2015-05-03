#include "atari.h"

static void			add_score(int val)
{
	t_game		*game;
	t_level		*cur_level;

	game = get_game();
	cur_level = game->cur_level;
	cur_level->score += val;
}

int					rebound(t_ball *ball, t_brick *brick, int side)
{
	if (brick->val != STATIC_BRICK)
	{
		add_score(brick->val);
		brick->val--;
	}
	if (side == 1 || side == 3)
		ball->speedy = -ball->speedy;
	if (side == 2 || side == 4)
		ball->speedx = -ball->speedx;
	return (1);
}
