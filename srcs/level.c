#include "atari.h"

static t_bool		is_level_complete(t_level *level)
{
	if (level->active_bricks)
		return (FALSE);
	return (TRUE);
}

void				load_level(t_game *game, int level_index)
{
	if (level_index >= 0 && level_index < N_LEVELS)
	{
		game->cur_level_index = level_index;
		game->cur_level = game->levels[game->cur_level_index];
	}
	else
	{
		ft_putendl("congratz!");
		sleep(1);
		free_all();
		exit(EXIT_SUCCESS);
	}
}

void				handle_levels(t_game *game)
{
	t_level		*cur_level;

	cur_level = game->cur_level;
	if (is_level_complete(cur_level))
	{
		load_level(game, game->cur_level_index + 1);
	}
	if (!INVINCIBLE_MODE && cur_level->lives <= 0)
	{
		ft_putendl("game over!");
		sleep(1);
		free_all();
		exit(EXIT_SUCCESS);
	}
}
