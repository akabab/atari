/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 17:52:18 by ycribier          #+#    #+#             */
/*   Updated: 2015/05/03 15:40:30 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atari.h"

void		handle_arrow_keys(t_keys *keys, int key, int action) //27
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_RIGHT)
			keys->right = TRUE;
		if (key == GLFW_KEY_LEFT)
			keys->left = TRUE;
		if (key == GLFW_KEY_UP)
			keys->up = TRUE;
		if (key == GLFW_KEY_DOWN)
			keys->down = TRUE;
	}
	if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_RIGHT)
			keys->right = FALSE;
		if (key == GLFW_KEY_LEFT)
			keys->left = FALSE;
		if (key == GLFW_KEY_UP)
			keys->up = FALSE;
		if (key == GLFW_KEY_DOWN)
			keys->down = FALSE;
	}
}

t_keys		*init_keys(void)
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
