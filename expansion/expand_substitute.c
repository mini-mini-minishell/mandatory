/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_substitute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:21:20 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 10:28:40 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_pattern(char *target)
{
	t_size	i;
	int		quote_flag;

	i = 0;
	quote_flag = QUOT_NON;
	while (target[i] != '\0' && target[i] != '\001')
	{
		quote_flag = check_quote(target[i], quote_flag);
		i++;
	}
	return (target[i] == '\001' && quote_flag == QUOT_NON);
}

static void	do_substitute(t_list **info_new_addr, \
			t_node *curr, t_list *temp_list)
{
	t_word_data	*word_data;

	while (curr)
	{
		word_data = curr->data;
		if (is_pattern(word_data->word) && word_data->variables)
		{
			while (word_data->variables->count)
				list_push_back(temp_list, \
					list_pop_head(word_data->variables));
			free(word_data->variables);
			word_data->variables = NULL;
		}
		curr = curr->next;
	}
	if (temp_list->count)
	{
		word_list_remove_all(*info_new_addr);
		*info_new_addr = temp_list;
	}
	else
		free(temp_list);
}

void	substitute_filename(t_list **info_new_addr)
{
	t_node		*curr;
	t_list		*temp_list;

	curr = (*info_new_addr)->head;
	if (curr)
	{
		temp_list = ft_malloc(sizeof(t_list));
		list_init(temp_list);
		do_substitute(info_new_addr, curr, temp_list);
	}
}
