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
	// ++(lexer->input); 이것도 됨
	lexer->input += lexer->index;
	lexer->index = 1;
	return (RV_SUCCESS);
}

t_return_value	space_meet_dquot(t_all_data *all_data)
{
	t_lexer	*lexer;

	lexer = &(all_data->lexer);
	lexer->current_state = LS_DQUOT;
	// ++(lexer->input); 이것도 됨
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
