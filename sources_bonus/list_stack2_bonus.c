/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_stack2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:22:26 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/15 10:48:02 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
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
