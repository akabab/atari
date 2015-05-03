#include "atari.h"

static void			draw_circle(float pos_x, float pos_y)
{
	float			x;
	float			y;
	float			radius;

	radius = 0.02f;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if ((x * x + y * y) <= (radius * radius))
			{
				glPointSize(1);
				glBegin(GL_POINTS);
				glColor3ub(PINK);
				glVertex2f(pos_x + x, pos_y + y);
				glEnd();
			}
			x += 0.0025f;
		}
		y += 0.0025f;
	}
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

void				draw_text(float x, float y, char *str, void *font)
{
	int		len;
	int		i;

	glRasterPos2f(x, y);
	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		glutBitmapCharacter(font, str[i]);
		i++;
	}
}

void				draw_score(int score)
{
	char	*tmp;
	char	*score_str;

	score_str = ft_itoa(score);
	tmp = ft_strjoin("SCORE: ", score_str);
	glColor3ub(WHITE);
	draw_text(UI_SCORE_X, UI_SCORE_Y, tmp, TEXT_FONT);
	ft_strdel(&score_str);
	ft_strdel(&tmp);
}
