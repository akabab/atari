#include "atari.h"
#include "libft.h"
#include <fcntl.h>

void	display_level(t_level *level)
{
	int i;
	int j;

	j = 0;
	while (j < LEVEL_HEIGHT)
	{
		i = 0;
		while (i < LEVEL_WIDTH)
		{
			ft_putnbr(level->blocks[j][i]);
			i++;
		}
		j++;
		ft_putendl("");
	}
}

void	draw_level(t_level *level)
{
	int i;
	int j;

	float block_w = 2.0f / (LEVEL_WIDTH + 0.01f);
	float block_h = 0.5f / (LEVEL_HEIGHT + 0.01f);

	j = 0;
	while (j < LEVEL_HEIGHT)
	{
		i = 0;
		while (i < LEVEL_WIDTH)
		{
			if (level->blocks[j][i])
			{
				int val = level->blocks[j][i];
				switch (val)
				{
					case 1:
						glColor3f(0.0f, 0.0f, 0.8f);
						break;
					case 3:
						glColor3f(0.0f, 0.8f, 0.0f);
						break;
					case 9:
						glColor3f(0.5f, 0.0f, 0.0f);
						break;
				}
				glRectf(-1.f + (float)i * block_w, 1.f - (float)j * block_h,
						-1.f + (float)(i+1) * block_w, 1.f - (float)(j+1) * block_h);
			}
			i++;
		}
		j++;
	}
}

void	parse_level(int fd, t_level *level)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (i >= LEVEL_HEIGHT)
		{
			ft_printf("Err: %s: wrong height\n", __func__);
			exit(EXIT_FAILURE);
		}
		if (line && ft_strlen(line) != LEVEL_WIDTH)
		{
			ft_printf("Err: %s: wrong width\n", __func__);
			exit(EXIT_FAILURE);
		}

		//set_level_blocks
		j = 0;
		while (line[j] != '\0')
		{
			int val;
			if (line[j] == NO_BLOCK_CHAR)
				val = 0;
			else
				val = line[j] - '0';
			level->blocks[i][j] = val;
			j++;
		}
		//

		if (line)
			ft_strdel(&line);
		i++;
	}
	if (i != LEVEL_HEIGHT)
	{
		ft_printf("Err: %s: wrong height\n", __func__);
		exit(EXIT_FAILURE);
	}
	// display_level(level);
}

void	load_levels(t_level levels[])
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
		ft_printf("loading %s ..\n", path);
		if ((fd[i] = open(path, O_RDONLY)) == -1)
			exit(EXIT_FAILURE);
		parse_level(fd[i], &levels[i]);
		ft_strdel(&path);
		ft_strdel(&level_index);
		i++;
	}
}
