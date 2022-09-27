/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:21:18 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/27 19:42:56 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_status;

static char	*extract_name(char *target)
{
	t_size	i;
	char	*name;

	i = isname_get_length(target);
	name = NULL;
	if (i > 0)
	{
		name = ft_malloc(sizeof(char) * (i + 1));
		ft_strlcpy(name, target, i + 1);
	}
	return (name);
}

char	*get_expanded_string(t_list *env, char **word, char **name)
{
	char	*value;

	value = NULL;
	if (**word == '?')
	{
		++(*word);
		value = ft_itoa(g_exit_status);
		if (!value)
			exit(2);
	}
	else
	{
		*name = extract_name(*word);
		if (*name)
		{
			*word += ft_strlen(*name);
			value = ft_strdup(envp_search_value(*env, *name));
		}
	}
	return (value);
}
