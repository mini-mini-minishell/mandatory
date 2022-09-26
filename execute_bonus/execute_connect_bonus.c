/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_connect_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:20:57 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:20:21 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
#include <stdlib.h>

static int	execute_list(t_cmd *cmd, int fd_info[3])
{
	int		return_value;

	if (cmd->content.connect.token & TT_AND)
	{
		return_value = execute_command(cmd->content.connect.left, \
				fd_info);
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
