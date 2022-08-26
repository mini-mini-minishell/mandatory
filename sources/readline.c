#include "../includes/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

int	g_exit_status;

void handler(int signum)
{
	if (signum != SIGINT)
		return;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	// rl_redisplay();
}

// static void	set_handler_reset_minishline(int sig)
// {
// 	ft_putstr_fd("\n", 1);
// 	if (sig != 0)
// 	{
// 		g_exit_status = 128 + sig;
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

// void	set_prompt_handler(void)
// {
// 	signal(SIGINT, set_handler_reset_minishline);
// 	signal(SIGQUIT, SIG_IGN);
// }

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
