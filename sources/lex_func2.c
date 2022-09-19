/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_func2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:22:15 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/14 20:22:16 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_return_value	space_meet_others(t_all_data *all_data)
{
	t_lexer	*lexer;

	lexer = &(all_data->lexer);
	lexer->current_state = LS_OTHERS;
	++(lexer->input);
	return (RV_SUCCESS);
}

t_return_value	space_meet_space(t_all_data *all_data)
{
	t_lexer	*lexer;

	lexer = &(all_data->lexer);
	++(lexer->input);
	return (RV_SUCCESS);
}

t_return_value	space_meet_squot(t_all_data *all_data)
{
	t_lexer	*lexer;

	lexer = &(all_data->lexer);
	lexer->current_state = LS_SQUOT;
	lexer->input += lexer->index;
	lexer->index = 1;
	return (RV_SUCCESS);
}

t_return_value	space_meet_dquot(t_all_data *all_data)
{
	t_lexer	*lexer;

	lexer = &(all_data->lexer);
	lexer->current_state = LS_DQUOT;
	lexer->input += lexer->index;
	lexer->index = 1;
	return (RV_SUCCESS);
}

t_return_value	space_meet_item(t_all_data *all_data)
{
	t_lexer	*lexer;

	lexer = &(all_data->lexer);
	lexer->last_item = (lexer->input)[lexer->index];
	lexer->current_state = LS_ITEM;
	lexer->input += lexer->index;
	lexer->index = 1;
	return (RV_SUCCESS);
}
