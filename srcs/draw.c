#include "atari.h"

static void		draw_level_border(void)
{
	glColor3ub(PURPLE);
	glRectf(NW_CORNER, NE_CORNER - LEVEL_MARGIN); //top
	glRectf(NW_CORNER, -1.f + LEVEL_MARGIN, -1.f); //left
	glRectf(1.f - LEVEL_MARGIN, 1.f, SE_CORNER); //right
}

void			draw_brick(t_brick *brick)
{
	int		val;

	glColor3ub(BLACK);
	glRectf(brick->x0, brick->y0, brick->x1, brick->y1);
	val = brick->val;
	if (val == 1) //USE MACROS
		glColor3ub(GREEN);
	else if (val == 2)
		glColor3ub(ORANGE);
	else if (val == 3)
		glColor3ub(PINK);
	else if (val == 9)
		glColor3ub(LIGHT_GREY);
	else
		glColor3ub(CYAN);
	glRectf(brick->x0 + BRICK_BORDER, brick->y0 - BRICK_BORDER,
			brick->x1 - BRICK_BORDER, brick->y1 + BRICK_BORDER);
}

void			draw_level(t_level *level)
{
	t_list_node		*cursor;
	t_brick			*cur_brick;

	draw_level_border();
	cursor = level->brick_list;
	while (cursor)
	{
		cur_brick = (t_brick *)cursor->value;
		if (cur_brick->val > 0)
			draw_brick(cur_brick);
		cursor = cursor->next;
	}
}
