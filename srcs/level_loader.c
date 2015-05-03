#include "atari.h"
#include <fcntl.h>

static void		push_level_brick(t_level *level, int x, int y, int val)
{
	t_brick		*new_brick;

	new_brick = (t_brick *)ft_memalloc(sizeof(t_brick));
	new_brick->x0 = -1.f + LEVEL_MARGIN + (float)x * BRICK_WIDTH;
	new_brick->y0 = 1.f - (LEVEL_MARGIN + (float)(y + 1) * BRICK_HEIGHT);
	new_brick->x1 =  -1.f + LEVEL_MARGIN + (float)(x + 1) * BRICK_WIDTH;
	new_brick->y1 = 1.f - (LEVEL_MARGIN + (float)y * BRICK_HEIGHT);
	new_brick->val = val;
	list_push_back(&level->brick_list, new_brick);
}

static void		parse_level(int fd, t_level *level)
{
	char	*line;
	int		x;
	int		y;

	y = 0;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (y >= LEVEL_HEIGHT)
			handle_errors(__func__, "wrong height!", TRUE);
		if (line && ft_strlen(line) != LEVEL_WIDTH)
			handle_errors(__func__, "wrong width!", TRUE);
		x = 0;
		while (line[x] != '\0')
		{
			if (line[x] != NO_BRICK_CHAR)
				push_level_brick(level, x, y, line[x] - '0');
			x++;
		}
		if (line)
			ft_strdel(&line);
		y++;
	}
	if (y != LEVEL_HEIGHT)
		handle_errors(__func__, "wrong height!", TRUE);
}

static t_level	*init_level(void)
{
	t_level	*level;

	level = (t_level *)ft_memalloc(sizeof(t_level));
	if (!level)
		exit(EXIT_FAILURE);
	level->score = INIT_SCORE;
	level->lives = INIT_LIVES;
	level->brick_list = NULL;
	level->ball = init_ball();
	level->pad = init_pad();
	return (level);
}

void			load_levels(t_level *levels[])
{
	int		fd[N_LEVELS];
	int		i;
	char	*path;
	char	*level_index;

	i = 0;
	while (i < N_LEVELS)
	{
		level_index = ft_itoa(i);
		path = ft_strjoin(LEVEL_PATH, level_index);
		ft_printf("loading %s ..\n", path); //
		if ((fd[i] = open(path, O_RDONLY)) == -1)
			exit(EXIT_FAILURE);
		levels[i] = init_level();
		parse_level(fd[i], levels[i]);
		ft_strdel(&path);
		ft_strdel(&level_index);
		i++;
	}
}
