/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:22:28 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:25:50 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
#include <stdlib.h>

t_item_type	get_item_type(char c)
{
	if (c == ' ')
		return (ITEM_SPACE);
	if (c == '\t')
		return (ITEM_TAB);
	if (c == '\n')
		return (ITEM_NL);
	if (c == '|')
		return (ITEM_PIPE);
	if (c == '&')
		return (ITEM_AND);
	if (c == '(')
		return (ITEM_LPAREN);
	if (c == ')')
		return (ITEM_RPAREN);
	if (c == '<')
		return (ITEM_LESS);
	if (c == '>')
		return (ITEM_GREATER);
	return (NOT_ITEM);
}

static t_token_type	get_token_type(char *content)
{
	if (*content == '\0')
		return (TT_EOF);
	if (get_item_type(*content) == NOT_ITEM)
		return (TT_WORD);
	if (!ft_strncmp(content, "(", 2))
		return (TT_PAREN_LEFT);
	if (!ft_strncmp(content, ")", 2))
		return (TT_PAREN_RIGHT);
	if (!ft_strncmp(content, "|", 2))
		return (TT_PIPE);
	if (!ft_strncmp(content, "||", 3))
		return (TT_OR);
	if (!ft_strncmp(content, "&&", 3))
		return (TT_AND);
	if (!ft_strncmp(content, "<", 2))
		return (TT_REDIR_IN);
	if (!ft_strncmp(content, ">", 2))
		return (TT_REDIR_OUT);
	if (!ft_strncmp(content, "<<", 3))
		return (TT_REDIR_HEREDOC);
	if (!ft_strncmp(content, ">>", 3))
		return (TT_REDIR_APPEND);
	return (TT_ERR);
}

t_token_data	*create_token_data(t_all_data *all_data)
{
	t_token_data	*new;
	t_lexer			*lexer;

	lexer = &all_data->lexer;
	new = ft_malloc(sizeof(t_token_data));
	new->content = ft_substr(lexer->input, 0, lexer->index);
	new->token_type = get_token_type(new->content);
	return (new);
}

void	add_new_token(t_all_data *all_data)
{
	t_list	*token_list;
	t_node	*new;

	token_list = &all_data->token_list;
	new = list_new_node(create_token_data(all_data));
	list_push_back(token_list, new);
}
