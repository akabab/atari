#include "atari.h"

void	handle_errors(const char __func[], char *err, t_bool is_critic)
{
	ft_printf("Err: %s: %s\n", __func, err);
	if (is_critic)
		exit(EXIT_FAILURE);
}
