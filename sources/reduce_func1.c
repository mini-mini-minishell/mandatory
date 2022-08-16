#include "../includes/minishell.h"

t_return_value	reduce_rule_0(t_all_data *all_data)
{
	int			count;
	t_parser	*parser;

	parser = &all_data->parser;
	count = 2 * 1;
	stack_pop_back(&parser->parser_stack, count);
	list_push_back(&parser->parser_stack, list_new_node(create_parser_data()));
	push_parser_stack(parser, SYMBOL_START);
	parser->flag |= PARSER_FINISH;
	parser->final_cmd = parser->value_stack->content.cmd;
	return (RV_SUCCESS);
}

t_return_value	reduce_rule_1(t_all_data *all_data)
{

}

//list_push_back(&parser->parser_stack, list_new_node(create_parser_data()));


