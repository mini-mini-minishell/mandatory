/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_stack2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:22:26 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/19 16:01:25 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

t_redir_data	*create_redir_data(void)
{
	t_redir_data	*new;

	new = ft_malloc(sizeof(t_redir_data));
	return (new);
}

t_parser_state	parser_peek_state(t_list parser_stack)
{
	t_parser_data	*data;

	data = parser_stack.tail->data;
	if (data->type & PARSER_STATE)
		return (data->state);
	else
	{
		data = parser_stack.tail->prev->data;
		return (data->state);
	}
}

void	stack_pop_back(t_list *list, int count)
{
	t_node	*temp;
	int		i;

	i = 0;
	while (i < count)
	{
		temp = list_pop_back(list);
		free(temp->data);
		free(temp);
		++i;
	}
}
