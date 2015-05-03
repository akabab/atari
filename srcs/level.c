#include "atari.h"

static t_bool		is_level_complete(t_level *level)
{
	t_list_node		*cursor;
	t_brick			*cur_brick;

	cursor = level->brick_list;
	while (cursor)
	{
		cur_brick = (t_brick *)cursor->value;
		if (cur_brick->val != STATIC_BRICK && cur_brick->val > 0)
			return (FALSE);
		cursor = cursor->next;
	}
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
		//congratz -> game finished
		ft_putendl("congratz");
		exit(EXIT_SUCCESS);
	}
}

void				handle_levels(t_game *game)
{
	if (is_level_complete(game->cur_level))
	{
		//load next lvl
		ft_putendl("load next lvl");
		load_level(game, game->cur_level_index + 1);
	}
}
