#include "../includes/minishell.h"
#include <stdlib.h>

// SUB -> paren_left L paren_right
t_return_value	reduce_rule_10(t_all_data *all_data)
{
	int				count;
	t_tree_content	content;
	t_parser		*parser;
	t_tree_content	l;
	t_tree_data		*data;

	parser = &all_data->parser;
	count = 2 * 3;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_back(&parser->parser_stack, TT_SUBSHELL);
	data = parser->tree_stack.tail->prev->data;
	l = data->content;
	content.cmd = make_subshell(l.cmd);
	stack_pop_back(&parser->tree_stack, 3);
	tree_push_back(&parser->tree_stack, content);
	data = parser->tree_stack.tail->data;
	data->type = TREE_CMD;
	return (RV_SUCCESS);
}

// RL -> RL R;
t_return_value	reduce_rule_11(t_all_data *all_data)
{
	int				count;
	t_tree_content	content;
	t_parser		*parser;
	t_list			*redir;
	t_tree_data		*data;

	parser = &all_data->parser;
	count = 2 * 2;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_back(&parser->parser_stack, TT_REDIR_LIST);
	data = parser->tree_stack.tail->prev->data;
	redir = data->content.redir_list;
	content.redir_list = redir;
	data = parser->tree_stack.tail->data;
	data->content.redir_list->head->prev = redir->tail;
	redir->tail->next = data->content.redir_list->head;
	redir->tail = data->content.redir_list->tail;
	stack_pop_back(&parser->tree_stack, 2);
	tree_push_back(&parser->tree_stack, content);
	data = parser->tree_stack.tail->data;
	data->type = TREE_REDIR_LIST;
	return (RV_SUCCESS);
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
	parser_push_back(&parser->parser_stack, TT_REDIR_LIST);
	data = parser->tree_stack.tail->data;
	redir = data->content;
	content.redir_list = redir.redir_list;
	stack_pop_back(&parser->tree_stack, 1);
	tree_push_back(&parser->tree_stack, content);
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
	parser_push_back(&parser->parser_stack, TT_ELEMENT);
	data = parser->tree_stack.tail->data;
	word = data->content;
	content.element = ft_malloc(sizeof(t_element));
	content.element->word = word.word;
	content.element->redir_list = NULL;
	stack_pop_back(&parser->tree_stack, 1);
	tree_push_back(&parser->tree_stack, content);
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
	parser_push_back(&parser->parser_stack, TT_ELEMENT);
	data = parser->tree_stack.tail->data;
	redir = data->content;
	content.element = ft_malloc(sizeof(t_element));
	content.element->redir_list = redir.redir_list;
	content.element->word = NULL;
	stack_pop_back(&parser->tree_stack, 1);
	tree_push_back(&parser->tree_stack, content);
	data = parser->tree_stack.tail->data;
	data->type = TREE_ELEMENT;
	return (RV_SUCCESS);
}
