#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	check_directory_name_input(t_cmd *cmd, char **directory_name)
{
	if (!cmd->content.simple.words->count || check_one_word(cmd, '~'))
	{
		*directory_name = ft_strdup(envp_search_value(*cmd->envp_list, "HOME"));
		if (!*directory_name)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (EXECUTION_FAILURE);
		}
	}
	else if (cmd->content.simple.words->count != 1)
	{
		ft_putstr_fd("cd: Too many arguments\n", STDERR_FILENO);
		return (EXECUTION_FAILURE);
	}
	else if (check_one_word(cmd, '-'))
	{
		envp_search_value(*cmd->envp_list, "OLDPWD");
		*directory_name = ft_strdup(envp_search_value(*cmd->envp_list, "OLDPWD"));
		if (!*directory_name)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
			return (EXECUTION_FAILURE);
		}
	}
	return (EXECUTION_SUCCESS);
}

static int	get_directory_name(t_cmd *cmd, char **directory_name)
{
	t_word_data	*data;
	int			return_value;

	return_value = check_directory_name_input(cmd, directory_name);
	if (cmd->content.simple.words->head)
		data = cmd->content.simple.words->head->data;
	if (return_value == EXECUTION_SUCCESS && *directory_name == NULL)
		*directory_name = ft_strdup(data->word);
	return (return_value);
}

static int	change_directory(t_cmd *cmd, char *directory_name)
{
	int			return_value;

	return_value = replace_pwd(ft_strdup("OLDPWD"), cmd);
	if (return_value == EXECUTION_SUCCESS)
	{
		return_value = chdir(directory_name);
		if (return_value == EXECUTION_SUCCESS)
		{
			return_value = replace_pwd(ft_strdup("PWD"), cmd);
		}
		else if (return_value == -1)
		{
			ft_putstr_fd("cd: ", STDERR_FILENO);
			ft_putstr_fd(directory_name, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		}
	}
	if (return_value == EXECUTION_SUCCESS)
		return (EXECUTION_SUCCESS);
	else
		return (EXECUTION_FAILURE);
}

int	ft_cd(t_cmd *cmd)
{
	char	*directory_name;
	int		return_value;

	directory_name = NULL;
	return_value = get_directory_name(cmd, &directory_name);
	if (return_value == EXECUTION_SUCCESS)
	{
		return_value = change_directory(cmd, directory_name);
		free(directory_name);
	}
	return (return_value);
}
