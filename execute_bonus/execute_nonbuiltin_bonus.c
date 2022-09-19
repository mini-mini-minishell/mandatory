/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_nonbuiltin_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:21:04 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/15 10:44:12 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

static int	print_err_msg_return_status(int err)
{
	if (err != 0)
	{
		errno = err;
		ft_putstr_fd(": command not found\n", 2);
		return (EX_NOEXEC);
	}
	else
	{
		ft_putstr_fd(": command not found\n", 2);
		return (EX_NOTFOUND);
	}
}

static int	try_execute_in_path(char **cmd_array, \
					char **paths, char **env_array)
{
	t_size	index;
	char	*full_path;
	int		err;

	index = 0;
	err = 0;
	while (paths[index])
	{
		full_path = get_full_path(paths[index], cmd_array[0]);
		execve(full_path, cmd_array, env_array);
		if (errno != ENOENT)
			err = errno;
		free(full_path);
		++index;
	}
	return (print_err_msg_return_status(err));
}

static int	try_direct_execve(char **cmd_array, char **env_array)
{
	execve(cmd_array[0], cmd_array, env_array);
	if (errno == ENOENT)
	{
		ft_putstr_fd(": directory not found\n", 2);
		return (EX_NOTFOUND);
	}
	return (EX_NOEXEC);
}

static void	free_3_doubles(char **array1, char **array2, char **array3)
{
	free_double(array1);
	free_double(array2);
	free_double(array3);
}

int	execute_nonbuiltin(t_cmd *cmd)
{
	char	**argv;
	char	**envp;
	char	**paths;
	int		return_value;

	argv = trans_word_list_2_array(*(cmd->content.simple.words));
	envp = trans_envp_list_2_array(*cmd->envp_list);
	if (ft_strchr(argv[0], '/') == 0)
	{
		paths = parse_envp(envp);
		if (paths)
		{
			return_value = try_execute_in_path(argv, paths, envp);
			free_3_doubles(argv, envp, paths);
			return (return_value);
		}
	}
	return_value = try_direct_execve(argv, envp);
	free_3_doubles(argv, envp, NULL);
	return (return_value);
}
