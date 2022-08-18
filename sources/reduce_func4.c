#include "../includes/minishell.h"

// R -> redir_op id;
t_return_value	reduce_rule_15(t_all_data *all_data)
{
	int				count;
	t_parser		*parser;
	t_tree_content	content;
	t_tree_content	word;
	t_tree_content	redir_open;
	t_tree_data		*data;

	count = 2 * 2;
	parser = &all_data->parser;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_stack(&parser->parser_stack, TT_REDIR);
	data = parser->tree_stack.tail->data;
	word = data->content;
	data = parser->tree_stack.tail->prev->data;
	redir_open = data->content;
	content.redir_list = make_redir(word.word, redir_open.token);
	stack_pop_back(&parser->tree_stack, 2);
	tree_push_back(&parser->tree_stack, content);
	data = parser->tree_stack.tail->data;
	data->type = TREE_REDIR_LIST;
	if (redir_open.token == TT_REDIR_HEREDOC)
		gather_heredoc(parser); // push_heredoc임 고치셈.
		// push_heredoc(parser, content.redir_list);
	return (RV_SUCCESS);
}
