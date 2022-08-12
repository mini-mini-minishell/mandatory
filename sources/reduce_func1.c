#include "../includes/minishell.h"

t_return_value	reduce_rule_0(t_all_data *all_data)
{
	int	count;

	count = 2 * 1;
	pop_parser_stack(parser, count);
	push_parser_stack(parser, SYMBOL_START);
	parser->flag |= PARSER_FINISH;
	parser->final_cmd = parser->value_stack->content.cmd;
	return (RV_SUCCESS);
}