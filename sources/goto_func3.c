/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goto_func3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:22:05 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/14 20:22:06 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parser_state	goto_from_state_16(t_token_type type)
{
	if (type & TT_CONNECT_GROUP)
		return (STATE_11);
	if (type & TT_PAREN_RIGHT)
		return (STATE_21);
	return (STATE_NON);
}

t_parser_state	goto_from_state_18(t_token_type type)
{
	if (type & TT_PIPE)
		return (STATE_12);
	return (STATE_NON);
}
