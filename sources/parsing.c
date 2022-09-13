#include "../includes/minishell.h"
#include <stdlib.h>

void	check_arguments(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Wrong Arguments\n", 2);
		exit(EXIT_FAILURE);
	}
}
