
#include "../includes/minishell.h"
#include <stdio.h> //+++++++++++++++++++
#include <stdlib.h> //+++++++++++++++++++

static void	get_envp_list(t_list *envp_list, char **envp)
{
	int	index;

	index = 0;
	while(envp[index])
	{
		printf("%s\n", envp[index]);
		++index;
		//list_new_node()
	}
	exit(0); //++++++++++++
}


static void	get_envp(t_all_lists *all_lists, char **envp)
{
	t_list	envp_list;

	envp_list = all_lists->envp_list;
	list_init(&envp_list);
	get_envp_list(&envp_list, envp);
	//스플릿 -> '=', '\n' 얘 기준 스플릿해서 
	//t_env_data에 저장 key / value
}

void	init_all(t_all_lists *all_lists, char **envp)
{
	//init_lexing();
	//init_parsing();
	get_envp(all_lists, envp);
}