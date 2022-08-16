#include "../includes/minishell.h"

// SUB -> paren_left L paren_right // make subshell 안만듬!!!!
t_return_value	reduce_rule_10(t_all_data *all_data)
{
	int				count;
	t_tree_content	content;
	t_tree_content	l;

	count = 2 * 3;
	pop_parser_stack(parser, count);
	push_parser_stack(parser, SYMBOL_SUBSHELL);
	l = parser->value_stack->next->content;
	content.cmd = make_subshell(l.cmd);
	pop_value_stack(parser, 3);
	push_value_stack(parser, content);
	parser->value_stack->type = VALUE_CMD;
	return (0);
}

// RL -> RL R;
t_return_value	reduce_rule_11(t_all_data *all_data)
{
	int				count;
	t_tree_content	content;
	t_tree_content	redir_list;
	t_redir_list	*redir;

	count = 2 * 2;
	pop_parser_stack(parser, count);
	push_parser_stack(parser, SYMBOL_REDIR_LIST);
	redir_list = parser->value_stack->next->content;
	content.redir_list = redir_list.redir_list;
	redir = redir_list.redir_list;
	while (redir && redir->next)
		redir = redir->next;
	redir->next = parser->value_stack->content.redir_list;
	pop_value_stack(parser, 2);
	push_value_stack(parser, content);
	parser->value_stack->type = VALUE_REDIR_LIST;
	return (0);
}

// RL -> R;
t_return_value	reduce_rule_12(t_all_data *all_data)
{
	int				count;
	t_parser		*parser;
	t_tree_content	content;
	t_tree_content	redir;
	t_tree_data		*data;

	parser = &all_data->parser;
	count = 2 * 1;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_stack(&parser->parser_stack, TT_REDIR_LIST);
	data = parser->tree_stack.tail->data;
	redir = data->content;
	content.redir_list = redir.redir_list;
	stack_pop_back(&parser->tree_stack, 1);
	tree_push_back(parser, content);
	data = parser->tree_stack.tail->data;
	data->type = TREE_REDIR_LIST;
	return (RV_SUCCESS);
}

// ELEM -> id;
t_return_value	reduce_rule_13(t_all_data *all_data)
{
	int				count;
	t_parser		*parser;
	t_tree_content	content;
	t_tree_content	word;
	t_tree_data		*data;

	parser = &all_data->parser;
	count = 2 * 1;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_stack(&parser->parser_stack, TT_ELEMENT);
	data = parser->tree_stack.tail->data;
	word = data->content;
	content.element = ft_malloc(sizeof(t_element));
	content.element->word = word.word;
	content.element->redir_list = NULL;
	stack_pop_back(&parser->tree_stack, 1);
	tree_push_back(parser, content);
	data = parser->tree_stack.tail->data;
	data->type = TREE_ELEMENT;
	return (RV_SUCCESS);
}

// ELEM -> R;
t_return_value	reduce_rule_14(t_all_data *all_data)
{
	int				count;
	t_parser		*parser;
	t_tree_content	content;
	t_tree_content	redir;
	t_tree_data		*data;

	parser = &all_data->parser;
	count = 2 * 1;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_stack(&parser->parser_stack, TT_ELEMENT);
	data = parser->tree_stack.tail->data;
	redir = data->content;
	content.element = ft_malloc(sizeof(t_element));
	content.element->redir_list = redir.redir_list;
	content.element->word = NULL;
	stack_pop_back(&parser->tree_stack, 1);
	tree_push_back(parser, content);
	data = parser->tree_stack.tail->data;
	data->type = TREE_ELEMENT;
	return (RV_SUCCESS);
}
