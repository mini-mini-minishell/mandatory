/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:21:06 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/15 10:44:28 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
#include <stdlib.h>

static void	set_fd(int fd_info[3], int fd_read, int fd_write, int fd_close)
{
	fd_info[READ_END] = fd_read;
	fd_info[WRITE_END] = fd_write;
	fd_info[CLOSE_END] = fd_close;
}

static void	open_pipe_if_needed(t_cmd *cmd, int fildes[2])
{
	if (cmd->flag & CMD_FLAG_NEED_PIPE)
	{
		ft_pipe(fildes);
	}
	else
	{
		fildes[READ_END] = NO_PIPE;
		fildes[WRITE_END] = NO_PIPE;
	}
}

int	execute_single_pipe(t_cmd *cmd, int fd_info[3])
{
	pid_t		pid;
	int			fildes1[2];
	int			fildes2[2];

	ft_pipe(fildes1);
	set_fd(fd_info, NO_PIPE, fildes1[WRITE_END], fildes1[READ_END]);
	execute_command_internal(cmd->content.connect.left, fd_info);
	ft_close(fildes1[WRITE_END]);
	open_pipe_if_needed(cmd, fildes2);
	set_fd(fd_info, fildes1[READ_END], fildes2[WRITE_END], fildes2[READ_END]);
	pid = ft_fork();
	if (pid == 0)
	{
		set_handler_for_default();
		cmd->content.connect.right->flag |= CMD_FLAG_IS_FORKED;
		execute_command(cmd->content.connect.right, fd_info);
	}
	cmd->pid_last_child = pid;
	ft_close(fildes1[READ_END]);
	ft_close(fildes2[WRITE_END]);
	set_fd(fd_info, fildes2[READ_END], NO_PIPE, NO_PIPE);
	return (0);
}

int	execute_pipe(t_cmd *cmd, int fd_info[3])
{
	pid_t	pid;
	int		fildes[2];

	cmd->content.connect.left->flag |= CMD_FLAG_NEED_PIPE;
	execute_command_internal(cmd->content.connect.left, fd_info);
	open_pipe_if_needed(cmd, fildes);
	fd_info[WRITE_END] = fildes[WRITE_END];
	fd_info[CLOSE_END] = fildes[READ_END];
	pid = ft_fork();
	if (pid == 0)
	{
		set_handler_for_default();
		cmd->content.connect.right->flag |= CMD_FLAG_IS_FORKED;
		execute_command(cmd->content.connect.right, fd_info);
	}
	cmd->pid_last_child = pid;
	ft_close(fd_info[READ_END]);
	ft_close(fildes[WRITE_END]);
	set_fd(fd_info, fildes[READ_END], NO_PIPE, NO_PIPE);
	return (0);
}
