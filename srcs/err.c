#include "atari.h"

void	handle_errors(const char func[], char *err, t_bool is_critic)
{
	ft_printf("Err: %s: %s\n", func, err);
	if (is_critic)
		exit(EXIT_FAILURE);
}
