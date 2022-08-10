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
//++++++++++++++++++++++++++++++++++++++++++++++++++
static t_token_type	get_token_type(char *content)
{
	if (*content == '\0')
		return (TT_EOF);
	if (ft_ismetachar(*content) == META_NON) //++++++++
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
	new->token_type = get_token_type(new->content);
	return (new);
}

//+++++++++++++++++++++++++++++
t_list	*add_new_token(t_all_data *all_data)
{
	t_list	*token_list

	new = //++++++++++++++++++++++++++++++++
}
