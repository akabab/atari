#include "atari.h"

static void		reset_keys(t_keys *keys)
{
	keys->right = FALSE;
	keys->left = FALSE;
	keys->up = FALSE;
	keys->down = FALSE;
}

void			handle_arrow_keys(t_keys *keys, int key, int action)
{
	if (action == GLFW_PRESS)
	{
		reset_keys(keys);
		if (key == GLFW_KEY_RIGHT)
			keys->right = TRUE;
		else if (key == GLFW_KEY_LEFT)
			keys->left = TRUE;
		else if (key == GLFW_KEY_UP)
			keys->up = TRUE;
		else if (key == GLFW_KEY_DOWN)
			keys->down = TRUE;
	}
	if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_RIGHT)
			keys->right = FALSE;
		else if (key == GLFW_KEY_LEFT)
			keys->left = FALSE;
		else if (key == GLFW_KEY_UP)
			keys->up = FALSE;
		else if (key == GLFW_KEY_DOWN)
			keys->down = FALSE;
	}
}

t_keys			*init_keys(void)
{
	t_keys		*keys;

	keys = ft_memalloc(sizeof(keys));
	if (!keys)
		exit(EXIT_FAILURE);
	keys->up = FALSE;
	keys->down = FALSE;
	keys->right = FALSE;
	keys->left = FALSE;
	return (keys);
}
