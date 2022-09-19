/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:20:47 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/15 10:41:36 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
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

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = ft_strdup(envp_search_value(*cmd->envp_list, "PWD"));
		if (!pwd)
			return (print_error());
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
	return (0);
}
