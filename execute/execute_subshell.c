/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:21:09 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/15 10:44:48 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

int	execute_subshell(t_cmd *cmd, int fd_info[3])
{
	pid_t	pid;

	cmd->content.subshell.cmd->envp_list = cmd->envp_list;
	cmd->content.subshell.cmd->exit_status = cmd->exit_status;
	pid = ft_fork();
	if (pid == 0)
	{
		set_handler_for_default();
		if (do_redirections(fd_info, cmd->redir_list, cmd->envp_list) < 0)
			exit(EXIT_FAILURE);
		cmd->content.subshell.cmd->flag |= CMD_FLAG_IS_FORKED;
		execute_command(cmd->content.subshell.cmd, fd_info);
	}
	cmd->pid_last_child = pid;
	return (0);
}
