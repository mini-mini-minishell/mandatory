#include "../includes/minishell.h"
#include <stdio.h>

// struct s_parser_data
// {
// 	int				type;
// 	t_token_type	token;
// 	t_parser_state	state;
// };

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
