#include "../includes/minishell.h"
#include <stdio.h>

t_redir_data	*create_redir_data(void)
{
	t_redir_data	*new;

	new = ft_malloc(sizeof(t_redir_data));
	return (new);
}

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
