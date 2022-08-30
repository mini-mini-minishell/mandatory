#include "../includes/minishell.h"
#include <errno.h>

static int	print_error(void)
{
	char	*error_string;

	error_string = strerror(errno);
	while (*error_string)
	{
		if (ft_write(STDERR_FILENO, error_string, 1) > 0)
			error_string++;
	}
	ft_write(STDERR_FILENO, "\n", 1);
	return (EXECUTION_FAILURE);
}

char	*envp_search_value(t_list list, char *key)
{
	size_t		index;
	t_node		*current;
	size_t		key_len;
	t_env_data	*temp_data;

	if (!list.count)
		return (NULL);
	key_len = ft_strlen(key);
	current = list.head;
	index = 0;
	while (index < list.count)
	{
		temp_data = (t_env_data *)(current->data);
		if (!ft_strncmp(key, temp_data->key, key_len + 1))
			return (temp_data->value);
		current = current->next;
		++index;
	}
	return (NULL);
}

int	pwd(t_cmd *cmd, t_list	envp_list)
{
	char	*pwd;

	pwd = getcwd(NULL,0);
	if (!pwd)
	{
		pwd = ft_strdup(envp_search_value(cmp->envp_list, "PWD"));
		if (!pwd)
			return (print_error());
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
	return (0);
}