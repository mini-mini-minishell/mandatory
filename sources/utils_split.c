/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:23:06 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/14 20:23:07 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

static char	**free_str(char **str, int count)
{
	int	i;

	i = 0;
	while (i < count + 1)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_word_count(char const *s, char const *set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] && is_set(s[i], set))
			i++;
		else
		{
			count++;
			while (s[i] && !is_set(s[i], set))
				i++;
		}
	}
	return (count);
}

static void	make_str(char **result, char const *s, char *set, int count)
{
	int	i;
	int	j;
	int	ri;

	i = 0;
	ri = 0;
	while (ri < count && s[i] != '\0')
	{
		j = 0;
		while (is_set(s[i], set))
			i++;
		if (s[i] == '\0')
			break ;
		while (is_set(s[i + j], set) == 0 && s[i + j] != '\0')
			j++;
		result[ri] = ft_substr(s, i, j);
		if (result[ri] == NULL)
		{
			free_str(result, count);
			return ;
		}
		ri++;
		i = i + j + 1;
	}
}

char	**ft_split(char const *s, char *set)
{
	int		count;
	char	**result;

	count = ft_word_count(s, set);
	result = ft_malloc(sizeof(char *) * (count + 1));
	result[count] = NULL;
	make_str(result, s, set, count);
	return (result);
}
