
#include "../includes/minishell.h"
#include <stdlib.h>

void	print_envp(t_all_lists *all_lists)
{
	t_list		env;
	t_node		*current_node;
	t_env_data	*current_env;
	int			index;

	env = all_lists->envp_list;
	current_node = env.head;
	index = 0;
	while (index < env.count)
	{
		current_env = (t_env_data *)current_node->data;
		ft_putstr_fd(current_env->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(current_env->value, 1);
		ft_putstr_fd("\n", 1);
		current_node = current_node->next;
		++index;
	}
	exit(0); // ---------
}

void	init_all(t_all_lists *all_lists, char **envp)
{
	//init_lexing();
	//init_parsing();
	get_envp(all_lists, envp);
	print_envp(all_lists);
}