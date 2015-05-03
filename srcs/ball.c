#include <math.h>
#include <glfw3.h>
#include "libft.h"
#include "atari.h"
#include "ball.h"

int					initBall(t_ball *ball)
{
	ball->x = BALL_ORIGIN_X;
	ball->y = BALL_ORIGIN_Y;
	ball->r = BALL_RADIUS;
	ball->speed = BALL_ORIGIN_SPEED;
	ball->rad = BALL_MVT_ANGLE;
	return (1);
}

int					updateBall(t_ball *ball)
{
	ball->x += ball->speed * cos(ball->rad);
	ball->y += ball->speed * sin(ball->rad);
	if (!checkBounds(ball))
		return (0);
	checkCollisions(ball);
	return (1);
}

int					checkBounds(t_ball *ball)
{
	if ((ball->x + ball->r) >= (1.0f - LEVEL_MARGIN) ||
			(ball->x - ball->r) <= (-1.0f + LEVEL_MARGIN)
		ball->rad = fmod((M_PI - ball->rad), (2.0f * M_PI));
	if ((ball->y + ball->r) >= (1.0f - LEVEL_MARGIN) ||
		(ball->y - ball->r) <= (-1.0f + LEVEL_MARGIN))
		ball->rad = (ball->rad) * -1;
	//if (ball->y <= -1.0f)
	//	return (0);
	return (1);
}


void				drawBall(t_ball *ball)
{
	float			x;
	float			y;
	int				i;

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	i = 0;
	while (i < 20)
	{
		x = ball->x + ball->r * (cos(i * 2.0f * M_PI / 20.0f));
		y = ball->y + ball->r * (sin(i * 2.0f * M_PI / 20.0f));
		glVertex2f(x, y);
		i++;
	}
	glEnd();
}
