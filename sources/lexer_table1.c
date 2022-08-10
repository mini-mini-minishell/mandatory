#include "../includes/minishell.h"

int	get_next_char(t_all_data *all_data)
{
	t_lexer	*lexer;

	lexer = &(all_data->lexer);
	++(lexer->index);
	return (RV_SUCCESS);
}

int	others_meet_space(t_all_data *all_data)
{
	t_lexer	*lexer;

	lexer = &(all_data->lexer);
	lexer->current_state = LS_SPACE;

	lexer->input += lexer->index;
	lexer->index = 1;
	//실패 여부 판단
	return (RV_SUCCESS);
}