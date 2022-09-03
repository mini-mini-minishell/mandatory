#include "../includes/minishell.h"
#include <stdlib.h>

static int	execute_list(t_cmd *cmd, int fd_info[3])
{
	int		return_value;

	if (cmd->content.connect.token & TT_AND)
	{
		return_value = execute_command(cmd->content.connect.left, \
				fd_info);// int return 으로 execute_command 를 변경시 return이 int이므로 괜찮다
		if (return_value == EXECUTION_SUCCESS)
			return (execute_command(cmd->content.connect.right, \
						fd_info));
		else
			return (return_value);
	}
	else
	{
		return_value = execute_command(cmd->content.connect.left, \
				fd_info);
		if (return_value != EXECUTION_SUCCESS)
			return (execute_command(cmd->content.connect.right, \
						fd_info));
		else
			return (return_value);
	}
}

#include <stdio.h>
int	execute_connect(t_cmd *cmd, int fd_info[3])
{
	cmd->content.connect.left->envp_list = cmd->envp_list;
	cmd->content.connect.right->envp_list = cmd->envp_list;
	cmd->content.connect.left->exit_status = cmd->exit_status;
	cmd->content.connect.right->exit_status = cmd->exit_status;
	if (cmd->content.connect.token & TT_PIPE)
	{
		if (cmd->content.connect.left->type == CMD_SIMPLE)
		{
			cmd->content.connect.left->flag |= CMD_FLAG_NEED_FORK;
		}
		if (cmd->content.connect.left->type != CMD_CONNECT)
			return (execute_single_pipe(cmd, fd_info));
		return (execute_pipe(cmd, fd_info));
	}
	else
		return (execute_list(cmd, fd_info));
}
