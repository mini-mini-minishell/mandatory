#include "../includes/minishell.h"

t_return_value	turn_others(t_all_data *all_data)
{
    t_lexer	*lexer;

	lexer = &(all_data->lexer);
	lexer->current_state = LS_OTHERS;
	++(lexer->index);
	return (RV_SUCCESS);
}
