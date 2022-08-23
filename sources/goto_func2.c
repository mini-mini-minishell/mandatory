#include "../includes/minishell.h"

t_parser_state	goto_from_state_7(t_token_type type)
{
	if (type & TT_PAREN_LEFT)
		return (STATE_7);
	if (type & TT_WORD)
		return (STATE_8);
	if (type & TT_REDIR_GROUP)
		return (STATE_10);
	if (type & TT_LIST)
		return (STATE_16);
	if (type & TT_PIPELINE)
		return (STATE_2);
	if (type & TT_CMD)
		return (STATE_3);
	if (type & TT_SIMPLE)
		return (STATE_4);
	if (type & TT_SUBSHELL)
		return (STATE_5);
	if (type & TT_ELEMENT)
		return (STATE_6);
	if (type & TT_REDIR)
		return (STATE_9);
	return (STATE_NON);
}

t_parser_state	goto_from_state_10(t_token_type type)
{
	if (type & TT_WORD)
		return (STATE_17);
	return (STATE_NON);
}

t_parser_state	goto_from_state_11(t_token_type type)
{
	if (type & TT_PAREN_LEFT)
		return (STATE_7);
	if (type & TT_WORD)
		return (STATE_8);
	if (type & TT_REDIR_GROUP)
		return (STATE_10);
	if (type & TT_PIPELINE)
		return (STATE_18);
	if (type & TT_CMD)
		return (STATE_3);
	if (type & TT_SIMPLE)
		return (STATE_4);
	if (type & TT_SUBSHELL)
		return (STATE_5);
	if (type & TT_ELEMENT)
		return (STATE_6);
	if (type & TT_REDIR)
		return (STATE_9);
	return (STATE_NON);
}

t_parser_state	goto_from_state_12(t_token_type type)
{
	if (type & TT_PAREN_LEFT)
		return (STATE_7);
	if (type & TT_WORD)
		return (STATE_8);
	if (type & TT_REDIR_GROUP)
		return (STATE_10);
	if (type & TT_CMD)
		return (STATE_19);
	if (type & TT_SIMPLE)
		return (STATE_4);
	if (type & TT_SUBSHELL)
		return (STATE_5);
	if (type & TT_ELEMENT)
		return (STATE_6);
	if (type & TT_REDIR)
		return (STATE_9);
	return (STATE_NON);
}

t_parser_state	goto_from_state_14(t_token_type type)
{
	if (type & TT_REDIR_GROUP)
		return (STATE_10);
	if (type & TT_REDIR)
		return (STATE_20);
	return (STATE_NON);
}