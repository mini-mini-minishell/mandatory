#include "../includes/minishell.h"

t_return_value	reduce_rule_0(t_all_data *all_data)
{
	int			count;
	t_parser	*parser;
	t_tree_data	*tree_data;

	parser = &all_data->parser;
	tree_data = parser->tree_stack.tail->data;
	count = 2 * 1;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_back(&parser->parser_stack, TT_START);
	parser->flag |= PARSER_FINISH;
	parser->final_cmd = tree_data->cmd;
	return (RV_SUCCESS);
}

t_return_value	reduce_rule_1(t_all_data *all_data)
{
	int				count;
	t_parser		*parser;
	t_tree_content	content;
	t_tree_content	l;
	t_tree_content	p;
	t_token_type	connector;

	parser = &all_data->parser;
	count = 2 * 3;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_stack(&parser->parser_stack, TT_LIST);
	l = parser->tree_stack.tail->next->next->content;
	connector = parser->value_stack->next->content.token;
	p = parser->value_stack->content;
	content.cmd = make_connect(l.cmd, p.cmd, connector);
	stack_pop_back(&parser->tree_stack, 3);
	push_value_stack(parser, content);
	parser->value_stack->type = VALUE_CMD;
	return (0);
}

//list_push_back(&parser->parser_stack, list_new_node(create_parser_data()));


