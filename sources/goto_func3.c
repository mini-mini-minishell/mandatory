#include "../includes/minishell.h"

t_parser_state	goto_from_state_16(t_token_type type)
{
	if (type & TT_CONNECT_GROUP)
		return (STATE_11);
	if (type & TT_PAREN_RIGHT)
		return (STATE_21);
	return (STATE_NON);
}

t_parser_state	goto_from_state_18(t_token_type type)
{
	if (type & TT_PIPE)
		return (STATE_12);
	return (STATE_NON);
}