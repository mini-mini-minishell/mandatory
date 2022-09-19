/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_func4_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:22:18 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/15 10:47:29 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"

t_return_value	turn_others(t_all_data *all_data)
{
	t_lexer	*lexer;

	lexer = &(all_data->lexer);
	lexer->current_state = LS_OTHERS;
	++(lexer->index);
	return (RV_SUCCESS);
}
