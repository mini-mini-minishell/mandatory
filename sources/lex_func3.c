#include "../includes/minishell.h"
#include <stdio.h>

t_return_value	item_meet_others(t_all_data *all_data)
{
	t_lexer			*lexer;
	t_token_data	*token_data;

	lexer = &(all_data->lexer);
	lexer->last_item = (lexer->input)[lexer->index];
	lexer->current_state = LS_OTHERS;
	add_new_token(all_data);
	lexer->input += lexer->index;
	lexer->index = 1;
	token_data = (t_token_data *)(all_data->token_list.tail->data);
	if (token_data->token_type == TT_ERR)
	{
		printf("item meet others\n");
		return (RV_ERROR);
	}
	return (RV_SUCCESS);
}

t_return_value	item_meet_space(t_all_data *all_data)
{
	t_lexer			*lexer;
	t_token_data	*token_data;

	lexer = &(all_data->lexer);
	lexer->last_item = (lexer->input)[lexer->index];
	lexer->current_state = LS_SPACE;
	add_new_token(all_data);
	lexer->input += lexer->index;
	lexer->index = 1;
	token_data = (t_token_data *)(all_data->token_list.tail->data);
	if (token_data->token_type == TT_ERR)
	{
		printf("item_meet_space\n");
		return (RV_ERROR);
	}
	return (RV_SUCCESS);
}

t_return_value	item_meet_squot(t_all_data *all_data)
{
	t_lexer			*lexer;
	t_token_data	*token_data;

	lexer = &(all_data->lexer);
	lexer->last_item = (lexer->input)[lexer->index];
	lexer->current_state = LS_SQUOT;
	add_new_token(all_data);
	lexer->input += lexer->index;
	lexer->index = 1;
	token_data = (t_token_data *)(all_data->token_list.tail->data);
	if (token_data->token_type == TT_ERR)
	{
		printf("item_meet_squot\n");
		return (RV_ERROR);
	}
	return (RV_SUCCESS);
}

t_return_value	item_meet_dquot(t_all_data *all_data)
{
	t_lexer			*lexer;
	t_token_data	*token_data;

	lexer = &(all_data->lexer);
	lexer->last_item = (lexer->input)[lexer->index];
	lexer->current_state = LS_DQUOT;
	add_new_token(all_data);
	lexer->input += lexer->index;
	lexer->index = 1;
	token_data = (t_token_data *)(all_data->token_list.tail->data);
	if (token_data->token_type == TT_ERR)
	{
		printf("item_meet_dquot\n");
		return (RV_ERROR);
	}
	return (RV_SUCCESS);
}

#include <stdlib.h>

t_return_value	item_meet_item(t_all_data *all_data)
{
	char			next_char;
	t_lexer			*lexer;
	t_token_data	*token_data;


	lexer = &(all_data->lexer);
	next_char = (lexer->input)[lexer->index];
	if (next_char == '(' || next_char == ')' || \
			lexer->last_item != next_char)
	{
		add_new_token(all_data);
		lexer->input += lexer->index;
		lexer->index = 1;
		token_data = (t_token_data *)(all_data->token_list.tail->data);
		if (token_data->token_type == TT_ERR)
		{
			printf("item_meet_item\n");
			exit(0);
			return (RV_ERROR);
		}
	}
	else
		lexer->index += 1;
	lexer->last_item = next_char;
	return (RV_SUCCESS);
}
