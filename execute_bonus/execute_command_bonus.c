/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:20:55 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:20:19 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
#include <stdlib.h>

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

int	execute_command(t_cmd *cmd, int fd_info[3])
{
	int	return_value;
	int	wait_return;

	return_value = execute_command_internal(cmd, fd_info);
	wait_return = ft_waitchild(cmd);
	if (wait_return >= 0)
		return_value = wait_return;
	if (cmd->flag & CMD_FLAG_IS_FORKED)
		exit(return_value);
	return (return_value);
}
