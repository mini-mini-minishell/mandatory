#include "../includes/minishell.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (s == 0)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}
