#include "../includes/minishell.h"
// #include <unistd.h>
// #include <stdlib.h>
// #include <fcntl.h>

static int	dup2_pipe(int fd_info[3])
{
	if (fd_info[CLOSE_END] > 0)
		ft_close(fd_info[CLOSE_END]);
	if (fd_info[READ_END] > 0)
	{
		if (ft_dup2(fd_info[READ_END], STDIN_FILENO) < 0)
			return (-1);
		ft_close(fd_info[READ_END]);
	}
	if (fd_info[WRITE_END] > 0)
	{
		if (ft_dup2(fd_info[WRITE_END], STDOUT_FILENO) < 0)
			return (-1);
		ft_close(fd_info[WRITE_END]);
	}
	return (0);
}

#include <stdio.h>

static int	dup2_redir_list(t_list *redir_list, t_list *envp_list)
{
	t_redir_data	*redir_data;
	t_node			*current;
	
	if (!redir_list)
		return (0);
	current = redir_list->head;
	while (current)
	{
		redir_data = current->data;
		redir_data->fd_new = get_redir_fd(redir_data, envp_list);
		if (redir_data->fd_new < 0)
			return (-1);
		if (ft_dup2(redir_data->fd_new, redir_data->fd_orig) < 0)
			return (-1);
		ft_close(redir_data->fd_new);
		current = current->next;
	}
	return (0);
}

int	do_redirections(int fd_info[3], t_list *redir_list, t_list *env)
{
	if (dup2_pipe(fd_info) < 0)
		return (-1);
	if (dup2_redir_list(redir_list, env) < 0)
		return (-1);
	fd_info[READ_END] = NO_PIPE;
	fd_info[WRITE_END] = NO_PIPE;
	fd_info[CLOSE_END] = NO_PIPE;
	return (0);
}
