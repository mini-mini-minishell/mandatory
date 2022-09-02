#include "../includes/minishell.h"

int	execute_command_internal(t_cmd *cmd, int fd_info[3])
{
	if (cmd->type == CMD_SIMPLE)
	{
		return (execute_simple(cmd, fd_info));
	}
	else if (cmd->type == CMD_CONNECT)
	{
		return (execute_connect(cmd, fd_info));
	}
	else if (cmd->type == CMD_SUBSHELL)
	{
		return (execute_subshell(cmd, fd_info));
	}
	else
	{
		return (EXECUTION_FAILURE);
	}
}

#include <stdio.h>
int	execute_command(t_cmd *cmd, int fd_info[3])
{
	int	return_value;
	int	wait_return;

	// 우리가 돌게 한거!
	// data = cmd->content.simple.words->head->data;
	// built_in_fp = NULL;
	// built_in_fp = is_builtin(data->word);
	// execute_simple_internal(built_in_fp, cmd);

	return_value = execute_command_internal(cmd, fd_info);
	wait_return = ft_waitchild(cmd);
	if (wait_return >= 0)
		return_value = wait_return;
	if (cmd->flag & CMD_FLAG_IS_FORKED)
		exit(return_value);
	return (return_value);
}
