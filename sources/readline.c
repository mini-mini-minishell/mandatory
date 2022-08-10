#include "../includes/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signum)
{
	write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void    prompt_loop(t_all_data *all_data)
{
    char *line;

    while (1)
    {
        line = readline("minishell > ");
        if (line)
        {
			ft_putstr_fd("output> ", 1);
        	ft_putstr_fd(line, 1);
        	ft_putstr_fd("\n", 1);
            add_history(line);
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