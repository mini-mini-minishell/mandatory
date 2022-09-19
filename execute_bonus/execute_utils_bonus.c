/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:21:11 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/15 10:44:39 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"

int	save_fd_status(int fd_buff[2])
{
	fd_buff[READ_END] = dup(STDIN_FILENO);
	fd_buff[WRITE_END] = dup(STDOUT_FILENO);
	return (0);
}

int	restore_fd_status(int fd_buff[2], int exit_status)
{
	ft_dup2(fd_buff[READ_END], STDIN_FILENO);
	ft_close(fd_buff[READ_END]);
	ft_dup2(fd_buff[WRITE_END], STDOUT_FILENO);
	ft_close(fd_buff[WRITE_END]);
	return (exit_status);
}

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	ft_waitchild(t_cmd *cmd)
{
	int	status;
	int	waitpid_return;
	int	return_value;

	return_value = -1;
	while (1)
	{
		waitpid_return = waitpid(-1, &status, 0);
		if (waitpid_return < 0)
			break ;
		if (waitpid_return == cmd->pid_last_child)
			return_value = get_exit_status(status);
	}
	return (return_value);
}

int	is_quoted(char *word)
{
	while (*word)
	{
		if (*word == '\'' || *word == '"')
			return (1);
		word++;
	}
	return (0);
}
