/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:23:04 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:26:28 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
#include <stdlib.h>
#include <unistd.h>

t_pid	ft_fork(void)
{
	t_pid	pid;

	pid = fork();
	if (pid < 0)
		exit_with_message("Fork Error");
	return (pid);
}

int	ft_pipe(int heredoc_fd[2])
{
	int	return_value;	

	return_value = pipe(heredoc_fd);
	if (return_value)
		exit_with_message("Pipe Error");
	return (RV_SUCCESS);
}

int	ft_close(int fd)
{
	int	result;

	if (fd <= 2)
		return (0);
	result = close(fd);
	if (result < 0)
		exit_with_message("Close Error");
	return (result);
}

int	ft_dup2(int fd1, int fd2)
{
	int	result;

	result = dup2(fd1, fd2);
	if (result < 0)
		ft_putstr_fd(": dup error\n", 2);
	return (result);
}
