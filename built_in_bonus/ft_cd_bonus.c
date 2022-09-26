/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:20:21 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:18:34 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
#include <stdlib.h>

static int	check_directory_failure(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	return (EXECUTION_FAILURE);
}

static int	check_directory_name_input(t_cmd *cmd, char **directory_name)
{
	if (!cmd->content.simple.words->count || check_one_word(cmd, '~'))
	{
		*directory_name = ft_strdup(envp_search_value(*cmd->envp_list, "HOME"));
		if (!*directory_name)
			return (check_directory_failure("cd: HOME not set\n"));
	}
	else if (cmd->content.simple.words->count != 1)
		return (check_directory_failure("cd: Too many arguments\n"));
	else if (check_one_word(cmd, '-'))
	{
		envp_search_value(*cmd->envp_list, "OLDPWD");
		*directory_name = \
			ft_strdup(envp_search_value(*cmd->envp_list, "OLDPWD"));
		if (!*directory_name)
			return (check_directory_failure("cd: OLDPWD not set\n"));
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
