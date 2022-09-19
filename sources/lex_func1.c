/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_func1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:22:14 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/14 20:22:14 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

t_return_value	get_next_char(t_all_data *all_data)
{
	t_lexer	*lexer;

	lexer = &(all_data->lexer);
	++(lexer->index);
	return (RV_SUCCESS);
}

t_return_value	others_meet_space(t_all_data *all_data)
{
	t_lexer			*lexer;
	t_token_data	*token_data;

	lexer = &(all_data->lexer);
	lexer->current_state = LS_SPACE;
	add_new_token(all_data);
	lexer->input += lexer->index;
	lexer->index = 1;
	token_data = (t_token_data *)(all_data->token_list.tail->data);
	if (token_data->token_type == TT_ERR)
		return (RV_ERROR);
	return (RV_SUCCESS);
}

t_return_value	others_meet_squot(t_all_data *all_data)
{
	t_lexer			*lexer;

	lexer = &(all_data->lexer);
	lexer->current_state = LS_SQUOT;
	++(lexer->index);
	return (RV_SUCCESS);
}

t_return_value	others_meet_dquot(t_all_data *all_data)
{
	t_lexer			*lexer;

	lexer = &(all_data->lexer);
	lexer->current_state = LS_DQUOT;
	++(lexer->index);
	return (RV_SUCCESS);
}

t_return_value	others_meet_item(t_all_data *all_data)
{
	t_lexer			*lexer;
	t_token_data	*token_data;

	lexer = &(all_data->lexer);
	lexer->last_item = (lexer->input)[lexer->index];
	lexer->current_state = LS_ITEM;
	add_new_token(all_data);
	lexer->input += lexer->index;
	lexer->index = 1;
	token_data = (t_token_data *)(all_data->token_list.tail->data);
	if (token_data->token_type == TT_ERR)
	{
		return (RV_ERROR);
	}
	return (RV_SUCCESS);
}
