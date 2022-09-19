/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_nosplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:21:17 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/14 20:21:17 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expand_variable_nosplit(char *value, \
							char **curr_word, t_list **info_new_addr)
{
	t_word_data	*data;
	char		*prev_word;

	if ((*info_new_addr)->tail)
	{
		data = (*info_new_addr)->tail->data;
		prev_word = data->word;
		data->word = ft_strjoin(prev_word, value);
	}
	else
	{
		list_push_back(*info_new_addr, list_new_node \
						(create_word_data(ft_strjoin(*curr_word, value))));
	}
	data = (*info_new_addr)->tail->data;
	*curr_word = data->word;
	if (value)
		free(value);
	return (0);
}
