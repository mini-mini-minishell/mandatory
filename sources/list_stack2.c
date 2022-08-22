#include "../includes/minishell.h"

t_parser_state	parser_peek_state(t_list parser_stack)
{
	t_parser_data	*data;
	
	data = parser_stack.tail->data;
	if (data->type & PARSER_STATE)
		return (data->state);
	else
	{
		data = parser_stack.tail->prev->data;
		return (data->state);
	}
}
