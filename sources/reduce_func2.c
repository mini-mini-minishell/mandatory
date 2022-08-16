#include "../includes/minishell.h"

// C -> SC;
t_return_value	reduce_rule_5(t_all_data *all_data)
{
	int				count;
	t_parser		*parser;
	t_tree_content	content;
	t_tree_data		*sc;
	t_tree_data		*data;

	parser = &all_data->parser;
	count = 2 * 1;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_stack(&parser->parser_stack, TT_CMD);
	sc = parser->tree_stack.head->data;
	content.cmd = sc->content.cmd;
	stack_pop_back(&parser->tree_stack, 1);
	tree_push_back(parser, content);
	data = parser->tree_stack.head->data;
	data->type = TREE_CMD;
	return (RV_SUCCESS);
}

// C -> SUB;
int	reduce_rule_6(t_all_data *all_data)
{
	int				count;
	t_parser		*parser;
	t_tree_content	content;
	t_tree_data		*sub;
	t_tree_data		*data;

	parser = &all_data->parser;
	count = 2 * 1;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_stack(&parser->parser_stack, TT_CMD);
	sub = parser->tree_stack.head->data;
	content.cmd = sub->content.cmd;
	stack_pop_back(&parser->tree_stack, 1);
	tree_push_back(parser, content);
	data = parser->tree_stack.head->data;
	data->type = TREE_CMD;
	return (RV_SUCCESS);
}

// C -> SUB RL;
int	reduce_rule_7(t_all_data *all_data)
{
	int				count;
	t_parser		*parser;
	t_tree_content	content;
	t_tree_data		*sub;
	t_tree_data		*data;

	parser = &all_data->parser;
	count = 2 * 2;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_stack(&parser->parser_stack, TT_CMD);
	sub = parser->tree_stack.head->data;
	content.cmd = sub->content.cmd;
	data = parser->tree_stack.head->data;
	content.cmd->redir_list = data->content.redir_list;
	stack_pop_back(&parser->tree_stack, 2);
	tree_push_back(parser, content);
	data = parser->tree_stack.head->data;
	data->type = TREE_CMD;
	return (RV_SUCCESS);
}

// SC -> SC ELEM; //make simple 아직 안만든!!!!!!!!!!!!!!!!-----
int	reduce_rule_8(t_all_data *all_data)
{
	int				count;
	t_value_content	content;
	t_value_content	elem;
	t_value_content	simple;

	count = 2 * 2;
	pop_parser_stack(parser, count);
	push_parser_stack(parser, SYMBOL_SIMPLE);
	elem = parser->value_stack->content;
	simple = parser->value_stack->next->content;
	content.cmd = make_simple(simple.cmd, elem.element);
	pop_value_stack(parser, 2);
	push_value_stack(parser, content);
	parser->value_stack->type = VALUE_CMD;
	return (0);
}

// SC -> ELEM;
int	reduce_rule_9(t_parser *parser)
{
	int				count;
	t_value_content	content;
	t_value_content	elem;

	count = 2 * 1;
	pop_parser_stack(parser, count);
	push_parser_stack(parser, SYMBOL_SIMPLE);
	elem = parser->value_stack->content;
	content.cmd = make_simple(NULL, elem.element);
	pop_value_stack(parser, 1);
	push_value_stack(parser, content);
	parser->value_stack->type = VALUE_CMD;
	return (0);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++