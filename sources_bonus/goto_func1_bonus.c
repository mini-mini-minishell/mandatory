/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goto_func1_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:22:02 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/15 10:46:35 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
#include <stdio.h>

t_parser_state	goto_from_state_0(t_token_type type)
{
	if (type & TT_PAREN_LEFT)
		return (STATE_7);
	if (type & TT_WORD)
		return (STATE_8);
	if (type & TT_REDIR_GROUP)
		return (STATE_10);
	if (type & TT_LIST)
		return (STATE_1);
	if (type & TT_PIPELINE)
		return (STATE_2);
	if (type & TT_CMD)
		return (STATE_3);
	if (type & TT_SIMPLE)
		return (STATE_4);
	if (type & TT_SUBSHELL)
		return (STATE_5);
	if (type & TT_ELEMENT)
		return (STATE_6);
	if (type & TT_REDIR)
		return (STATE_9);
	return (STATE_NON);
}

t_parser_state	goto_from_state_1(t_token_type type)
{
	if (type & TT_CONNECT_GROUP)
		return (STATE_11);
	return (STATE_NON);
}

t_parser_state	goto_from_state_2(t_token_type type)
{
	if (type & TT_PIPE)
		return (STATE_12);
	return (STATE_NON);
}

t_parser_state	goto_from_state_4(t_token_type type)
{
	if (type & TT_WORD)
		return (STATE_8);
	if (type & TT_REDIR_GROUP)
		return (STATE_10);
	if (type & TT_ELEMENT)
		return (STATE_13);
	if (type & TT_REDIR)
		return (STATE_9);
	return (STATE_NON);
}

t_parser_state	goto_from_state_5(t_token_type type)
{
	if (type & TT_REDIR_GROUP)
		return (STATE_10);
	if (type & TT_REDIR_LIST)
		return (STATE_14);
	if (type & TT_REDIR)
		return (STATE_15);
	return (STATE_NON);
}
