#ifndef ATARI_H
# define ATARI_H

// # define GLFW_INCLUDE_GLU

# include "libft.h"
# include "list.h"
# include "ball.h"

# include <glfw3.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define WIN_WIDTH	600
# define WIN_HEIGHT	600

# define LEVEL_WIDTH	15
# define LEVEL_HEIGHT	5
# define LEVEL_MARGIN	0.05f

# define BRICK_WIDTH	((2.0f - 2.f * LEVEL_MARGIN) / LEVEL_WIDTH)
# define BRICK_HEIGHT	((0.5f - 2.f * LEVEL_MARGIN) / LEVEL_HEIGHT)
# define BRICK_BORDER	0.008f

# define NO_BRICK_CHAR	'_'
# define STATIC_BRICK	9

# define N_LEVELS		3
# define LEVEL_PATH		"./levels/level_"

/*
**		COLOR
**						|R|, |G|, |B|
*/
# define PINK			217, 036, 105
# define PURPLE			157, 124, 255
# define CYAN			117, 176, 195
# define YELLOW			227, 219, 115
# define ORANGE			228, 126, 000
# define GREEN			177, 227, 054
# define BROWN			115, 111, 079
# define DARK_GREY		044, 044, 039
# define LIGHT_GREY		142, 143, 137
# define BLACK			000, 000, 000
# define WHITE			255, 255, 255

/*
**		CORNERS
**
**    NW      N     NE
**            1
**            |
**    W -1----|----1 E
**            |
**           -1
**    SW      S     SE
**
**                        X ,  Y
*/
# define N_X			 0.f
# define N_Y			       1.f
# define S_X			 0.f
# define S_Y			      -1.f
# define W_X			-1.f
# define W_Y			       0.f
# define E_X			 1.f
# define E_Y			       0.f

# define NW				-1.f,  1.f
# define NE				 1.f,  1.f
# define SE				 1.f, -1.f
# define SW				-1.f, -1.f

typedef struct		s_brick
{
	float			x0;
	float			y0;
	float			x1;
	float			y1;
	int				val;
}					t_brick;

typedef struct		s_level
{
	t_list_node		*brick_list;
}					t_level;

void				reset_viewport(GLFWwindow *window);

/*
**		glfw_handler.c
*/
int					glfw_init(GLFWwindow **window);
int					glfw_clean(GLFWwindow *window);

/*
**		draw.c
*/
void				draw_level(t_level *level);

/*
**		level_loader.c
*/
void				load_levels(t_level levels[]);

int					renderer(GLFWwindow *window, t_level *levels, t_ball *ball, int level_index);

/*
**		err.c
*/
void				handle_errors(const char __func[], char *err, t_bool is_critic);


#endif
