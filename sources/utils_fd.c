#include "../includes/minishell.h"
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
		ft_perror(NULL);
	return (result);
}
