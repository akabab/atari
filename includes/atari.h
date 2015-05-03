#ifndef ATARI_H
# define ATARI_H

# include <glfw3.h>
# include <GLUT/glut.h>

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# include "libft.h"
# include "list.h"

# define INVINCIBLE_MODE	0
# define WIN_RESIZABLE		0

# define SQRT_2				1.414213
# define PI					3.141592

# define WIN_WIDTH			600
# define WIN_HEIGHT			600

# define LEVEL_WIDTH		15
# define LEVEL_HEIGHT		5
# define LEVEL_MARGIN		0.05f
# define TOP_MARGIN			0.13f

# define BRICK_WIDTH		((2.0f - 2.f * LEVEL_MARGIN) / LEVEL_WIDTH)
# define BRICK_HEIGHT		((0.5f - 2.f * LEVEL_MARGIN) / LEVEL_HEIGHT)
# define BRICK_BORDER		0.008f

# define NO_BRICK_CHAR		'_'
# define STATIC_BRICK		9

# define N_LEVELS			9
# define LEVEL_PATH			"./levels/level_"

# define INIT_SCORE			0
# define INIT_LIVES			3

# define B(X)				brick->X
# define P(X)				pad->X

/*
**		COLOR
**							|R|, |G|, |B|
*/
# define PINK				217,  36, 105
# define PURPLE				157, 124, 255
# define CYAN				117, 176, 195
# define YELLOW				227, 219, 115
# define ORANGE				228, 126,   0
# define GREEN				177, 227,  54
# define BROWN				115, 111,  79
# define DARK_GREY			 44,  44,  39
# define LIGHT_GREY			142, 143, 137
# define BLACK				  0,   0,   0
# define WHITE				255, 255, 255

# define TEXT_FONT			GLUT_BITMAP_9_BY_15

/*
**		COORDS
*/
# define NW					-1.f,  1.f
# define NE					 1.f,  1.f
# define SE					 1.f, -1.f
# define SW					-1.f, -1.f

# define N_X				0.f
# define N_Y				1.f
# define S_X				0.f
# define S_Y				-1.f
# define W_X				-1.f
# define W_Y				0.f
# define E_X				1.f
# define E_Y				0.f

# define UI_LIFE_X			(-1.f + 0.1f)
# define UI_LIFE_Y			(1.f - 0.1f)
# define UI_LIFE_MARGIN		0.1f

# define UI_SCORE_X			(1.f - 0.4f)
# define UI_SCORE_Y			(1.f - 0.132f)

# define BALL_OUT_LIMIT		(-1.0f)

typedef struct		s_brick
{
	float			x0;
	float			y0;
	float			x1;
	float			y1;
	int				val;
}					t_brick;

# define BALL_ORIGIN_X		0.0f
# define BALL_ORIGIN_Y		(0.0f - 0.3f)
# define BALL_RADIUS		0.03f
# define BALL_ORIGIN_SPEEDX	0.018
# define BALL_ORIGIN_SPEEDY	0.025

typedef struct		s_ball
{
	float			x;
	float			y;
	float			r;
	float			speedx;
	float			speedy;
}					t_ball;

# define PAD_INIT_X			0.f
# define PAD_INIT_Y			(-1.f + 0.1f)
# define PAD_INIT_WIDTH		0.5f
# define PAD_INIT_HEIGHT	0.08f
# define PAD_INIT_SCALE		1.f
# define PAD_INIT_SPEED		0.03f

typedef struct		s_pad
{
	float			x0;
	float			y0;
	float			x1;
	float			y1;
	float			scale;
	float			speed;
}					t_pad;

typedef struct		s_level
{
	int				score;
	int				lives;
	t_list_node		*brick_list;
	t_pad			*pad;
	t_ball			*ball;
}					t_level;

typedef struct		s_keys
{
	t_bool			up;
	t_bool			down;
	t_bool			right;
	t_bool			left;
}					t_keys;

typedef struct		s_game
{
	t_level			*levels[N_LEVELS];
	t_level			*cur_level;
	int				cur_level_index;
	t_keys			*keys;
}					t_game;

/*
**		main.c
*/
t_game				*get_game(void);
void				reset_viewport(GLFWwindow *window);
void				free_all(void);

/*
**		ball.c
*/
void				update_ball(t_ball *ball, t_list_node *bricks);
void				handle_bounds(t_ball *ball);
t_ball				*init_ball(void);

/*
**		collision.c
*/
int					check_collisions(t_ball *ball, t_list_node *bricks);

/*
**		collision2.c
*/
int					check_tr_two(t_ball *ball, t_brick *brick);
int					check_tl_two(t_ball *ball, t_brick *brick);
int					check_bl_two(t_ball *ball, t_brick *brick);
int					check_br_two(t_ball *ball, t_brick *brick);

/*
**		rebound.c
*/
int					rebound(t_ball *ball, t_brick *brick, int side);

/*
**		glfw_handler.c
*/
int					init_glfw(GLFWwindow **window);
int					clean_glfw(GLFWwindow *window);

/*
**		draw.c
*/
void				draw_level(t_level *level);

/*
**		level_loader.c
*/
void				load_levels(t_level *levels[]);

/*
**		keys.c
*/
void				handle_arrow_keys(t_keys *keys, int key, int action);
t_keys				*init_keys(void);

/*
**		pad.c
*/
void				update_pad(t_pad *pad, t_ball *ball);
t_pad				*init_pad(void);

/*
**		err.c
*/
void				handle_errors(const char func[],
						char *err, t_bool is_critic);

/*
**		level.c
*/
void				load_level(t_game *game, int level_index);
void				handle_levels(t_game *game);

/*
**		draw_ui.c
*/
void				draw_text(float x, float y, char *str, void *font);
void				draw_lives(int n_lives);
void				draw_score(int score);

#endif
