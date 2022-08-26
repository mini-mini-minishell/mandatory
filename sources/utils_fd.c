#include "../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

/* t_pid	safe_fork(void)
{
	t_pid	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_perror(NULL);
		exit(1);
	}
	return (pid);
} */

int	safe_pipe(int heredoc_fd[2])
{
	int	return_value;	

	return_value = pipe(heredoc_fd);
	if (return_value)
		exit_with_message("Pipe Error");
	return (RV_SUCCESS);
}

/* int	safe_close(int fd)
{
	int	ret;

	if (fd <= 2)
		return (0);
	ret = close(fd);
	if (ret < 0)
		ft_perror(NULL);
	return (ret);
} */

/* int	safe_dup2(int fd1, int fd2)
{
	int	ret;

	ret = dup2(fd1, fd2);
	if (ret < 0)
		ft_perror(NULL);
	return (ret);
} */