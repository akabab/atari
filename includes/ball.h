#ifndef BALL_H
# define BALL_H

#include "list.h"
#include "atari.h"

# define BALL_ORIGIN_X 0.0f
# define BALL_ORIGIN_Y 0.0f
# define BALL_RADIUS 0.03f
# define SPEED_STEP 0.01f
# define SPEED_MODIFIER 5
# define BALL_ORIGIN_SPEED (SPEED_MODIFIER * SPEED_STEP)
# define BALL_MVT_ANGLE (5 * M_PI / 6)

typedef struct		s_ball
{
	float			x;
	float			y;
	float			r;
	float			speed;
	float			rad;
}					t_ball;

int					initBall(t_ball *ball);
int					updateBall(t_ball *ball);
int					checkBounds(t_ball *ball);
int					checkCollisions(t_ball *ball, t_list_node **bricks);
int					rebound(t_ball *ball, t_brick *brick, int side);
void				drawBall(t_ball *ball);

#endif