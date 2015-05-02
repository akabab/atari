#ifndef ATARI_H
# define ATARI_H

#include <stdlib.h>
#include "ball.h"

# define WIN_WIDTH	800
# define WIN_HEIGHT	600

# define LEVEL_WIDTH	15
# define LEVEL_HEIGHT	5

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

typedef struct		s_level
{
	int				blocks[LEVEL_HEIGHT][LEVEL_WIDTH];
}					t_level;

int					initGLFW(GLFWwindow **window);
int					cleanGLFW(GLFWwindow *window);

void				load_levels(t_level levels[]);
void				draw_level(t_level *level);

int					renderer(GLFWwindow *window, t_level *levels, t_ball *ball, int level_index);

#endif
