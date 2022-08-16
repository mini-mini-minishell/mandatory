#include "../includes/minishell.h"

// R -> redir_op id;
t_return_value	reduce_rule_15(t_parser *parser)
{
	int				count;
	t_value_content	content;
	t_value_content	word;
	t_value_content	redir_op;

	count = 2 * 2;
	pop_parser_stack(parser, count);
	push_parser_stack(parser, SYMBOL_REDIR);
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
