/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:22:09 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:25:18 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"

t_quot_state	check_quote(char word, int quote_flag)
{
	if (word == '\'')
	{
		if (!(quote_flag & QUOT_DOUBLE))
		{
			quote_flag ^= QUOT_SINGLE;
		}
	}
	else if (word == '"')
	{
		if (!(quote_flag & QUOT_SINGLE))
		{
			quote_flag ^= QUOT_DOUBLE;
		}
	}
	return (quote_flag);
}

char	*check_heredoc_eof(char *str)
{
	t_quot_state	quote_flag;
	char			*new_str;
	char			*temp;

	if (!str)
		return (NULL);
	quote_flag = QUOT_NON;
	new_str = ft_strdup("");
	while (*str)
	{
		if (quote_flag == check_quote(*str, quote_flag))
		{
			temp = ft_malloc(sizeof(char) * 2);
			ft_strlcpy(temp, str, 2);
			new_str = ft_strjoin_gnl(new_str, temp);
			free(temp);
			temp = NULL;
		}
		str++;
	}
	return (new_str);
}
