#include "../includes/minishell.h"

int ft_env(t_cmd *cmd)
{
	print_envp(*cmd->envp_list);
	return (EXECUTION_SUCCESS);
}
