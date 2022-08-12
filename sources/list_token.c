#include "../includes/minishell.h"
#include <stdlib.h>

t_node	*list_new_node(void *data)
{
	t_node	*new;

	new = ft_malloc(sizeof(t_node));
	new->data = data;
	new->next = NULL;
	return (new);
}

t_item_type	get_item_type(char *content)
{
	if (content == ' ')
		return (ITEM_SPACE);
	if (content == '\t')
		return (ITEM_TAB);
	if (content == '\n')
		return (ITEM_NL);
	if (content == '|')
		return (ITEM_PIPE);
	if (content == '&')
		return (ITEM_AND);
	if (content == '(')
		return (ITEM_LPAREN);
	if (content == ')')
		return (ITEM_RPAREN);
	if (content == '<')
		return (ITEM_LESS);
	if (content == '>')
		return (ITEM_GREATER);
	return (NOT_ITEM);
}

static t_token_type	get_token_type(char *content)
{
	if (*content == '\0')
		return (TT_EOF);
	if (get_item_type(*content) == NOT_ITEM)
		return (TT_WORD);
	if (!ft_strcmp(content, "("))
		return (TT_PAREN_LEFT);
	if (!ft_strcmp(content, ")"))
		return (TT_PAREN_RIGHT);
	if (!ft_strcmp(content, "|"))
		return (TT_PIPE);
	if (!ft_strcmp(content, "||"))
		return (TT_OR);
	if (!ft_strcmp(content, "&&"))
		return (TT_AND);
	if (!ft_strcmp(content, "<"))
		return (TT_REDIR_IN);
	if (!ft_strcmp(content, ">"))
		return (TT_REDIR_OUT);
	if (!ft_strcmp(content, "<<"))
		return (TT_REDIR_HEREDOC);
	if (!ft_strcmp(content, ">>"))
		return (TT_REDIR_APPEND);
	return (TT_ERR);
}

t_token_data	*create_token_data(t_all_data *all_data)
{
	t_token_data	*new;
	t_lexer			*lexer;

	lexer = &all_data->lexer;
	new = ft_malloc(sizeof(t_token_data));
	new->content = ft_substr(lexer->index, 0, lexer->index);
	// ft_substr의 처음 인자는 lexer->input 이여야한다? -hogkim
	new->token_type = get_token_type(new->content);
	return (new);
}

t_list	*add_new_token(t_all_data *all_data)
{
	t_list	*token_list;
	t_node	*new;

	token_list = &all_data->token_list;
	new = list_new_node(create_token_data(all_data));
	list_push_back(token_list, new);
}
