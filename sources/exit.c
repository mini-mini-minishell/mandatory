#include "../includes/minishell.h"
#include <stdlib.h>

void	exit_with_message(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}
