#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	check_word_set_dirname(t_cmd *cmd, char **directory_name)
{
	if (!cmd->content.simple.words->count || check_one_word(cmd, "~") == 0)
	{
		*directory_name = ft_strdup(ft_find_variable(cmd->env, "HOME"));
		if (*directory_name == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (EXECUTION_FAILURE);
		}
	}
	else if (cmd->content.simple.words->next != NULL)
	{
		ft_putstr_fd("cd: Too many arguments\n", STDERR_FILENO);
		return (EXECUTION_FAILURE);
	}
	else if (check_one_word(cmd, '-'))
	{
		*directory_name = ft_strdup(ft_find_variable(cmd->env, "OLDPWD"));
		if (*directory_name == NULL)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
			return (EXECUTION_FAILURE);
		}
	}
	return (EXECUTION_SUCCESS);
}

static int	get_directory_name(t_cmd *cmd, char **directory_name)
{
	int			return_value;
	t_word_data	*data;

	data = cmd->content.simple.words->tail->data;
	return_value = check_word_set_dirname(cmd, directory_name);
	if (return_value == EXECUTION_SUCCESS && *directory_name == NULL)
	{
		*directory_name = ft_strdup(data->word);
		
	}
	return (return_value);
}

static int	change_directory(t_cmd *cmd, char *dirname)
{
	int	return_value;

	return_value = bind_cwd_to("OLDPWD", cmd);
	if (return_value == EXECUTION_SUCCESS)
	{
		return_value = chdir(dirname);
		if (return_value == EXECUTION_SUCCESS)
		{
			return_value = bind_cwd_to("PWD", cmd);
		}
		else if (return_value == -1)
		{
			ft_putstr_fd("cd: ", STDERR_FILENO);
			ft_perror(dirname);
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