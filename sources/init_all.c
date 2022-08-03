
#include "../includes/minishell.h"

static void	get_envp(t_all_lists *all_lists, char **envp)
{
	all_lists->envp_list;
}

void	init_all(t_all_lists *all_lists, char **envp)
{
	init_lexing();
	init_parsing();
	get_envp(all_lists, envp);
}