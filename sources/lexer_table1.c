#include "../includes/minishell.h"

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

}
