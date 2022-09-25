/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_func4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:22:52 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/20 14:32:45 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	make_new_tree_content(t_parser *parser, t_tree_content *content)
{
	t_tree_data		*data;
	t_tree_content	word;
	t_tree_content	redir_open;
	t_node			*node;
	t_list			*redir_list;

	redir_list = ft_malloc(sizeof(t_list));
	list_init(redir_list);
	data = parser->tree_stack.tail->data;
	word = data->content;
	data = parser->tree_stack.tail->prev->data;
	redir_open = data->content;
	node = make_redir_node(word.word, redir_open.token);
	list_push_back(redir_list, node);
	content->redir_list = redir_list;
	if (redir_open.token == TT_REDIR_HEREDOC)
		heredoc_list_push_back(&parser->heredoc_list, \
				heredoc_list_new_node(redir_list->head));
}

// R -> redir_op id;
t_return_value	reduce_rule_15(t_all_data *all_data)
{
	int				count;
	t_parser		*parser;
	t_tree_content	content;
	t_tree_data		*data;

	count = 2 * 2;
	parser = &all_data->parser;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_back(&parser->parser_stack, TT_REDIR);
	make_new_tree_content(&all_data->parser, &content);
	stack_pop_back(&parser->tree_stack, 2);
	tree_push_back(&parser->tree_stack, content);
	data = parser->tree_stack.tail->data;
	data->tree_type = TREE_REDIR_LIST;
	return (RV_SUCCESS);
}
