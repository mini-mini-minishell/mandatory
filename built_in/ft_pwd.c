#include "../includes/minishell.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>

static int	print_error(void)
{
	char	*error_string;

	error_string = strerror(errno);
	ft_putstr_fd(error_string, 2);
	return (EXECUTION_FAILURE);
}

int	ft_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL,0);
	if (!pwd)
	{
		//unset -> pwd 잘 되는지
		pwd = ft_strdup(envp_search_value(*cmd->envp_list, "PWD"));
		if (!pwd)
			return (print_error());
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1); 
	free(pwd);
	return (0);
}
