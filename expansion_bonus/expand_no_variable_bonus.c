/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_no_variable_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:21:15 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/15 10:44:58 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"

static char	get_char_to_append(char curr_char, t_expansion_flag flag, \
		t_quot_state quote_flag)
{
	char	char_to_append;

	if (quote_flag == QUOT_NON && curr_char == '*')
	{
		char_to_append = '\001';
	}
	else if (!(flag & EXP_QUOT) || \
			quote_flag == check_quote(curr_char, quote_flag))
	{
		char_to_append = curr_char;
	}
	else
	{
		char_to_append = '\0';
	}
	return (char_to_append);
}

void	no_variable_expansion(char *word, t_expansion_flag flag, \
		t_expansion_info *info)
{
	char		char_to_append;
	char		*str;
	char		*temp;

	char_to_append = get_char_to_append(*word, flag, info->quote_flag);
	if (char_to_append)
	{
		str = ft_malloc(2);
		str[0] = char_to_append;
		str[1] = '\0';
		temp = info->curr_word;
		info->curr_word = ft_strjoin(info->curr_word, str);
		free(str);
		free(temp);
		update_last_node_word(info->new_list, info->curr_word);
	}
}
