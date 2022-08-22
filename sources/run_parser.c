#include "../includes/minishell.h"

int	run_parser(t_all_data *all_data)
{
	t_parser_state	state;
	t_reducer_fp	reduce_func;
	t_token_type	token_type;
	t_parser_state	goto_state;

	state = parser_peek_state(all_data->parser.parser_stack);
	if (parser->parser_stack->token_type & PARSER_STATE)
	{
		token_type = get_input_symbol_type(parser->input);
		if (should_reduce(state, token_type))
		{
			reduce_func = get_reduce_rule(state, table);
			if (reduce_func)
				return (reduce_func(parser));
			else
				return (-1);
		}
	}
	else
	{
		token_type = parser->parser_stack->content.symbol;
	}
	goto_state = get_goto_state(state, token_type);
	return (goto_next_state(parser, goto_state, token_type));
}
