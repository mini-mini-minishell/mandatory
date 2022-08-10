
#include "../includes/minishell.h"
#include <signal.h>

void	init_all(t_all_data *all_data, char **envp)
{
	init_lexing();
	//init_parsing();
	get_envp(all_data, envp);
	// print_envp(all_data);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}