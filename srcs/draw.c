#include "atari.h"

#include <stdio.h>

static void			draw_level_border(void)
{
	glColor3ub(PURPLE);
	glRectf(NW, NE - LEVEL_MARGIN); //top
	glRectf(NW, -1.f + LEVEL_MARGIN, -1.f); //left
	glRectf(1.f - LEVEL_MARGIN, 1.f, SE); //right
}

static void			draw_brick(t_brick *brick)
{
	int		val;

	glColor3ub(BLACK);
	glRectf(brick->x0, brick->y1, brick->x1, brick->y0);
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
	glRectf(brick->x0 + BRICK_BORDER, brick->y1 - BRICK_BORDER,
			brick->x1 - BRICK_BORDER, brick->y0 + BRICK_BORDER);
}

static void			draw_ball(t_ball *ball)
{
	float			x;
	float			y;
	int				i;

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
	float	x0;
	float	x1;

	glColor3ub(DARK_GREY);
	glRectf(pad->x0, pad->y1, pad->x1, pad->y0);
}

void				draw_circle(float pos_x, float pos_y)
{
	float		x;
	float		y;
	int			i;

	glBegin(GL_POLYGON);
	glColor3ub(PINK);
	i = 0;
	while (i < 20)
	{
		x = pos_x + 0.02f * (cos(i * 2.0f * M_PI / 20.0f));
		y = pos_y + 0.02f * (sin(i * 2.0f * M_PI / 20.0f));
		glVertex2f(x, y);
		i++;
	}
	glEnd();
}

void				draw_lives(int n_lives)
{
	int		i;

	i = 0;
	while (i < n_lives)
	{
		draw_circle(UI_LIFE_X + i * UI_LIFE_MARGIN + 0.0f, UI_LIFE_Y);
		draw_circle(UI_LIFE_X + i * UI_LIFE_MARGIN + 0.04f, UI_LIFE_Y);
		glBegin(GL_TRIANGLES);
		glColor3ub(PINK);
		glVertex2f(UI_LIFE_X + i * UI_LIFE_MARGIN + 0.02f, UI_LIFE_Y + -0.06f);
		glVertex2f(UI_LIFE_X + i * UI_LIFE_MARGIN + 0.061f, UI_LIFE_Y + 0.0f);
		glVertex2f(UI_LIFE_X + i * UI_LIFE_MARGIN + -0.022f, UI_LIFE_Y + 0.0f);
		glEnd();
		i++;
	}
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
}

