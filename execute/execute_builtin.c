/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:20:53 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 11:00:13 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_builtin_func(const char *word)
{
	const char	*shell_builtins[7] = \
	{
		"echo", "exit", "unset", "export", "cd", "pwd", "env"
	};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (word && !ft_strncmp(word, shell_builtins[i], \
			ft_strlen(shell_builtins[i]) + 1))
			break ;
		++i;
	}
	return (i);
}

t_built_in_fp	is_builtin(t_list *word_list)
{
	t_word_data			*data;
	char				*word;
	int					index;
	const t_built_in_fp	builtin_func_table[7] = \
	{
		ft_echo, ft_exit, ft_unset, ft_export, ft_cd, ft_pwd, ft_env
	};

	data = word_list->head->data;
	word = data->word;
	index = find_builtin_func(word);
	if (index > 6)
		return (NULL);
	return (builtin_func_table[index]);
}
