/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_parser_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:23:01 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:26:24 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
#include <stdio.h>

static t_reducer_fp	get_reduce_rule(t_parser_state state, t_reducer_fp *table)
{
	int	index;

	index = (int)(state ^ PARSER_STATE);
	return (table[index]);
}

static t_action_flag	find_action_table(t_parser_state state)
{
	if (state == STATE_1)
		return (AF_START);
	if (state == STATE_2 || state == STATE_18)
		return (AF_LIST);
	if (state == STATE_3 || state == STATE_19)
		return (AF_PIPELINE);
	if (state == STATE_4 || state == STATE_5 || state == STATE_14)
		return (AF_CMD);
	if (state == STATE_6 || state == STATE_13)
		return (AF_SIMPLE);
	if (state == STATE_21)
		return (AF_SUBSHELL);
	if (state == STATE_15 || state == STATE_20)
		return (AF_REDIR_LIST);
	if (state == STATE_8 || state == STATE_9)
		return (AF_ELEMENT);
	if (state == STATE_17)
		return (AF_REDIR);
	return (AF_NON);
}

static int	should_reduce(t_parser_state curr_state, t_token_type input_type)
{
	t_action_flag	action_flag;

	action_flag = find_action_table(curr_state);
	return (action_flag & input_type);
}

static t_token_type	get_input_token_type(t_list token_list)
{
	t_token_data	*data;

	if (!token_list.head)
		return (TT_EOF);
	data = token_list.head->data;
	return (data->token_type);
}

int	run_parser(t_all_data *all_data)
{
	t_parser_state	state;
	t_reducer_fp	reduce_func;
	t_token_type	token_type;
	t_parser_state	goto_state;
	t_parser_data	*data;

	state = parser_peek_state(all_data->parser.parser_stack);
	data = all_data->parser.parser_stack.tail->data;
	if (data->type & PARSER_STATE)
	{
		token_type = get_input_token_type(all_data->token_list);
		if (should_reduce(state, token_type))
		{
			reduce_func = get_reduce_rule(state, all_data->parser.reduce_func);
			if (reduce_func)
				return (reduce_func(all_data));
			else
				return (-1);
		}
	}
	else
		token_type = data->token;
	goto_state = get_goto_state(state, token_type);
	return (goto_next_state(all_data, goto_state, token_type));
}
