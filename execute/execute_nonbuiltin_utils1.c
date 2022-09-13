#include "../includes/minishell.h"

char	**parse_envp(char **env)
{
	t_size	index;
	char	**result;

	index = 0;
	while (env[index] && ft_strncmp(env[index], "PATH=", 5))
		index++;
	if (!env[index])
		return (NULL);
	result = ft_split(env[index] + 5, ":");
	return (result);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

void	free_double(char **array)
{
	t_size	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		++i;
	}
	free(array);
}

char	*get_full_path(char *path, char *cmd_name)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp, cmd_name);
	free(temp);
	return (full_path);
}
