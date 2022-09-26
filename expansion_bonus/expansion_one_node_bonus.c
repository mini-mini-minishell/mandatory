/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_one_node_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:21:30 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:21:15 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"

static void	init_info(t_expansion_info *info)
{
	info->curr_word = NULL;
	info->new_list = ft_malloc(sizeof(t_list));
	list_init(info->new_list);
	info->quote_flag = 0;
}

t_list	*expand_one_node(t_node *word_node, t_list *env, t_expansion_flag flag)
{
	t_expansion_info	info;
	t_word_data			*data;
	char				*word;

	init_info(&info);
	data = word_node->data;
	word = data->word;
	while (*word != '\0')
	{
		info.quote_flag = check_quote(*word, info.quote_flag);
		if ((flag & EXP_VARIABLE) && info.quote_flag != QUOT_SINGLE && \
				*word == '$')
			expand_variable(&word, env, &info);
		else
			no_variable_expansion(word++, flag, &info);
	}
	if (!info.new_list->count)
		list_push_back(info.new_list, \
						list_new_node(create_word_data(info.curr_word)));
	if (flag & EXP_ASTERISK)
		filename_expansion(&info.new_list);
	return (info.new_list);
}
