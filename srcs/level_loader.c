#include <fcntl.h>
#include <glfw3.h>
#include "atari.h"
#include "libft.h"

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

void	draw_level_border(void)
{
	glColor3ub(115, 111, 79); //brown
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


	float block_margin = 0.01f;
	draw_level_border();
	cursor = level->brick_list;
	while (cursor)
	{
		cur_brick = (t_brick *)cursor->value;

		//border color
		// glColor3ub(44, 44, 39); //dark_grey
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
				glColor3ub(217, 36, 105); //pink
				break;
			case 9:
				glColor3ub(142, 143, 137); //grey
				break;
		}
		glRectf(cur_brick->x0 + block_margin, cur_brick->y0 - block_margin,
				cur_brick->x1 - block_margin, cur_brick->y1 + block_margin);

		cursor = cursor->next;
	}

}

void	parse_level(int fd, t_level *level)
{
	char	*line;
	int		i;
	int		j;

	//init level
	level->brick_list = NULL;

	float block_w = ((2.0f - 2.f * LEVEL_MARGIN) / LEVEL_WIDTH);
	float block_h = ((0.5f - 2.f * LEVEL_MARGIN) / LEVEL_HEIGHT);

	printf("%f %f\n", block_w, block_h);

	j = 0;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (j >= LEVEL_HEIGHT)
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
		i = 0;
		while (line[i] != '\0')
		{
			int val;
			if (line[i] != NO_BLOCK_CHAR)
			{
				t_brick *new_brick = (t_brick *)ft_memalloc(sizeof (t_brick));
				new_brick->x0 = -1.f + LEVEL_MARGIN + (float)i * block_w;
				new_brick->y0 = 1.f - (LEVEL_MARGIN + (float)j * block_h);
				new_brick->x1 =  -1.f + LEVEL_MARGIN + (float)(i+1) * block_w;
				new_brick->y1 = 1.f - (LEVEL_MARGIN + (float)(j+1) * block_h);
				new_brick->val = line[i] - '0';
				list_push_back(&level->brick_list, new_brick);
			}
			i++;
		}
		//

		if (line)
			ft_strdel(&line);
		j++;
	}
	if (j != LEVEL_HEIGHT)
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
