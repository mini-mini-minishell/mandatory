#include "../includes/minishell.h"

// R -> redir_op id;
t_return_value	reduce_rule_15(t_all_data *all_data)
{
	int				count;
	t_parser		*parser;
	t_tree_content	content;
	t_tree_content	word;
	t_tree_data		*data;

	count = 2 * 2;
	parser = &all_data->parser;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_stack(&parser->parser_stack, TT_REDIR);
	data = parser->tree_stack.tail->data;
	word = data->content;

	int				count;
	t_value_content	content;
	t_value_content	word;
	t_value_content	redir_op;

	word = parser->value_stack->content;
	redir_op = parser->value_stack->next->content;
	content.redir_list = make_redir(word.word, redir_op.token);
	pop_value_stack(parser, 2);
	push_value_stack(parser, content);
	parser->value_stack->type = VALUE_REDIR_LIST;
	if (redir_op.token == SYMBOL_REDIR_HEREDOC)
	{
		push_heredoc(parser, content.redir_list);
	}
	return (0);
}

