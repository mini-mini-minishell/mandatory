/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_nosplit_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:21:17 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:21:03 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"

int	expand_variable_nosplit(char *value, \
							char **curr_word, t_list **info_new_addr)
{
	t_word_data	*data;

	if ((*info_new_addr)->tail)
	{
		data = (*info_new_addr)->tail->data;
		data->word = ft_strjoin_gnl(data->word, value);
	}
	else
	{
		list_push_back(*info_new_addr, list_new_node \
						(create_word_data(ft_strjoin_gnl(*curr_word, value))));
	}
	data = (*info_new_addr)->tail->data;
	*curr_word = data->word;
	if (value)
		free(value);
	return (0);
}
