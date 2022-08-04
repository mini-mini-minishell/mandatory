
#include "../includes/minishell.h"
#include <stdlib.h>

void	init_all(t_all_lists *all_lists, char **envp)
{
	//init_lexing();
	//init_parsing();
	get_envp(all_lists, envp);
	print_envp(all_lists);
}