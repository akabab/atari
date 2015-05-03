#include <fcntl.h>
#include <glfw3.h>
#include "atari.h"
#include "libft.h"

void	draw_level_border(void)
{
	glColor3ub(157, 124, 255); //violet
	//top
	glRectf(-1.f, 1.f, 1.f, 1.f - LEVEL_MARGIN);
	//left
	glRectf(-1.f, 1.f, -1.f + LEVEL_MARGIN, -1.f);
	//right
	glRectf(1.f - LEVEL_MARGIN, 1.f, 1.f, -1.f);
}

void	draw_level(t_level *level)
{
	t_list_node		*cursor;
	t_brick			*cur_brick;


	draw_level_border();
	cursor = level->brick_list;
	while (cursor)
	{
		cur_brick = (t_brick *)cursor->value;

		//border color
		glColor3ub(0, 0, 0);
		glRectf(cur_brick->x0, cur_brick->y0, cur_brick->x1, cur_brick->y1);
		switch (cur_brick->val)
		{
			case 1:
				glColor3ub(227, 219, 115); //yellow
				break;
			case 2:
				glColor3ub(228, 126, 0); //orange
				break;
			case 3:
				glColor3ub(217, 36, 105); //pink+
				break;
			case 9:
				glColor3ub(142, 143, 137); //grey
				break;
		}
		glRectf(cur_brick->x0 + BLOCK_BORDER, cur_brick->y0 - BLOCK_BORDER,
				cur_brick->x1 - BLOCK_BORDER, cur_brick->y1 + BLOCK_BORDER);

		cursor = cursor->next;
	}

}

void	init_level_block(t_level *level, int x, int y, int val)
{
	t_brick		*new_brick;

	new_brick = (t_brick *)ft_memalloc(sizeof(t_brick));
	new_brick->x0 = -1.f + LEVEL_MARGIN + (float)x * BLOCK_WIDTH;
	new_brick->y0 = 1.f - (LEVEL_MARGIN + (float)y * BLOCK_HEIGHT);
	new_brick->x1 =  -1.f + LEVEL_MARGIN + (float)(x+1) * BLOCK_WIDTH;
	new_brick->y1 = 1.f - (LEVEL_MARGIN + (float)(y+1) * BLOCK_HEIGHT);
	new_brick->val = val;
	list_push_back(&level->brick_list, new_brick);
}

void	parse_level(int fd, t_level *level)
{
	char	*line;
	int		x;
	int		y;

	y = 0;
	line = NULL;
	level->brick_list = NULL; // mv -> init_level
	while (get_next_line(fd, &line) > 0)
	{
		if (y >= LEVEL_HEIGHT)
			handle_errors(__func__, "wrong height!", TRUE);
		if (line && ft_strlen(line) != LEVEL_WIDTH)
			handle_errors(__func__, "wrong width!", TRUE);
		x = 0;
		while (line[x] != '\0')
		{
			if (line[x] != NO_BLOCK_CHAR)
				init_level_block(level, x, y, line[x] - '0');
			x++;
		}
		if (line)
			ft_strdel(&line);
		y++;
	}
	if (y != LEVEL_HEIGHT)
		handle_errors(__func__, "wrong height!", TRUE);
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
