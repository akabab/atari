#ifndef ATARI_H
# define ATARI_H

# define GLFW_INCLUDE_GLU

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

# define BLOCK_WIDTH	((2.0f - 2.f * LEVEL_MARGIN) / LEVEL_WIDTH)
# define BLOCK_HEIGHT	((0.5f - 2.f * LEVEL_MARGIN) / LEVEL_HEIGHT)
# define BLOCK_BORDER	0.008f

# define NO_BLOCK_CHAR	'_'
# define STATIC_BLOCK	9

# define N_LEVELS		3
# define LEVEL_PATH		"./levels/level_"

/*
**		COLOR
*/
# define RED			"31"
# define GREEN			"32"
# define YELLOW			"33"
# define BLUE			"34"
# define PINK			"35"
# define GRBL			"36"
# define GREY			"37"
# define NO				"0"
# define C(X)			"\033["X"m"
# define CC(X)			"\033[3"X"m"
# define CB(X)			"\x1B[48;1;"X"m"
# define CBNO			"\x1B[0m"


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

int					initGLFW(GLFWwindow **window);
int					cleanGLFW(GLFWwindow *window);

void				load_levels(t_level levels[]);
void				draw_level(t_level *level);

int					renderer(GLFWwindow *window, t_level *levels, t_ball *ball, int level_index);

void	handle_errors(const char __func[], char *err, t_bool is_critic);


#endif
