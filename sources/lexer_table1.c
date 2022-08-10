#include "../includes/minishell.h"

int	get_next_char(t_all_data *all_data)
{
	t_lexer	*lexer;

	lexer = &(all_data->lexer);
	++(lexer->index);
	return (RV_SUCCESS);
}

int	ordinary_meet_space(t_all_data *all_data)
{
	t_lexer	*lexer;

	lexer = &(all_data->lexer);
	lexer->current_state = LS_SPACE;
	
	//-------------------------

	++(lexer->index);
	return (RV_SUCCESS);
}