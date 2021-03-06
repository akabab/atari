#include "atari.h"

static void			draw_level_border(void)
{
	glColor3ub(PURPLE);
	glRectf(NW, NE - LEVEL_MARGIN);
	glRectf(NW, -1.f + LEVEL_MARGIN, -1.f);
	glRectf(1.f - LEVEL_MARGIN, 1.f, SE);
}

static void			draw_brick(t_brick *brick)
{
	int		val;

	glColor3ub(BLACK);
	glRectf(brick->x0, brick->y1,
			brick->x1, brick->y0);
	val = brick->val;
	if (val == 1)
		glColor3ub(GREEN);
	else if (val == 2)
		glColor3ub(ORANGE);
	else if (val == 3)
		glColor3ub(PINK);
	else if (val == STATIC_BRICK)
		glColor3ub(LIGHT_GREY);
	else
		glColor3ub(117 - val * 12, 176 - val * 12, 195 - val * 12);
	glRectf(brick->x0 + BRICK_BORDER, brick->y1 - BRICK_BORDER,
			brick->x1 - BRICK_BORDER, brick->y0 + BRICK_BORDER);
}

static void			draw_ball(t_ball *ball)
{
	float			x;
	float			y;

	y = -ball->r;
	while (y <= ball->r)
	{
		x = -ball->r;
		while (x <= ball->r)
		{
			if ((x * x + y * y) <= (ball->r * ball->r))
			{
				glPointSize(1);
				glBegin(GL_POINTS);
				glColor3f(0.0, 1.0, 1.0);
				glVertex2f(ball->x + x, ball->y + y);
				glEnd();
			}
			x += 0.0025f;
		}
		y += 0.0025f;
	}
}

static void			draw_pad(t_pad *pad)
{
	glColor3ub(DARK_GREY);
	glRectf(pad->x0, pad->y1, pad->x1, pad->y0);
}

void				draw_level(t_level *level)
{
	t_list_node		*cursor;
	t_brick			*cur_brick;

	cursor = level->brick_list;
	while (cursor)
	{
		cur_brick = (t_brick *)cursor->value;
		if (cur_brick->val > 0)
			draw_brick(cur_brick);
		cursor = cursor->next;
	}
	update_ball(level->ball, level->brick_list);
	draw_ball(level->ball);
	update_pad(level->pad, level->ball);
	draw_pad(level->pad);
	draw_level_border();
	draw_lives(level->lives);
	draw_score(level->score);
}
