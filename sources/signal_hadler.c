#include "../includes/minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <signal.h>

void	set_handler_for_heredoc(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

// void	set_handler_for_default(void)
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// }

// void	set_handler_to_ignore(void)
// {
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// }
