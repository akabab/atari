#include "atari.h"
#include "libft.h"
#include <fcntl.h>

void	parse_level(fd)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		ft_putendl(line);
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
		if (line)
			ft_strdel(&line);
		i++;
	}
	if (i != LEVEL_HEIGHT)
	{
		ft_printf("Err: %s: wrong height\n", __func__);
		exit(EXIT_FAILURE);
	}
}

void	load_levels()
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
		parse_level(fd[i]);
		ft_strdel(&path);
		ft_strdel(&level_index);
		i++;
	}
}
