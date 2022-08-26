#include "../includes/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

int	g_exit_status;

void	prompt_loop(t_all_data *all_data)
{
	char *line;

	while (1)
	{
		line = readline("minishell > ");
		if (line)
		{
			process_line(all_data, line);
			ft_putstr_fd("output> ", 1);
			ft_putstr_fd(line, 1);
			ft_putstr_fd("\n", 1);
			free(line);
			line = NULL;
		}
		else
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
	}
}
