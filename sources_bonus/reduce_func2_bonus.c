/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_func2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:22:47 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:26:11 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
#include <stdlib.h>
#include <stdio.h>

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
	parser_push_back(&parser->parser_stack, TT_CMD);
	sc = parser->tree_stack.tail->data;
	content.cmd = sc->content.cmd;
	stack_pop_back(&parser->tree_stack, 1);
	tree_push_back(&parser->tree_stack, content);
	data = parser->tree_stack.tail->data;
	data->tree_type = TREE_CMD;
	return (RV_SUCCESS);
}

// C -> SUB;
t_return_value	reduce_rule_6(t_all_data *all_data)
{
	int				count;
	t_parser		*parser;
	t_tree_content	content;
	t_tree_data		*sub;
	t_tree_data		*data;

	parser = &all_data->parser;
	count = 2 * 1;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_back(&parser->parser_stack, TT_CMD);
	sub = parser->tree_stack.tail->data;
	content.cmd = sub->content.cmd;
	stack_pop_back(&parser->tree_stack, 1);
	tree_push_back(&parser->tree_stack, content);
	data = parser->tree_stack.tail->data;
	data->tree_type = TREE_CMD;
	return (RV_SUCCESS);
}

// C -> SUB RL;
t_return_value	reduce_rule_7(t_all_data *all_data)
{
	int				count;
	t_parser		*parser;
	t_tree_content	content;
	t_tree_data		*sub;
	t_tree_data		*data;

	parser = &all_data->parser;
	count = 2 * 2;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_back(&parser->parser_stack, TT_CMD);
	sub = parser->tree_stack.tail->prev->data;
	content.cmd = sub->content.cmd;
	data = parser->tree_stack.tail->data;
	content.cmd->redir_list = data->content.redir_list;
	stack_pop_back(&parser->tree_stack, 2);
	tree_push_back(&parser->tree_stack, content);
	data = parser->tree_stack.tail->data;
	data->tree_type = TREE_CMD;
	return (RV_SUCCESS);
}

// SC -> SC ELEM; 
t_return_value	reduce_rule_8(t_all_data *all_data)
{
	t_parser		*parser;
	t_list			*tree;
	t_tree_data		*data;
	t_tree_content	content;
	t_element		*for_free;

	parser = &all_data->parser;
	stack_pop_back(&parser->parser_stack, 2 * 2);
	parser_push_back(&parser->parser_stack, TT_SIMPLE);
	tree = &parser->tree_stack;
	content.cmd = make_simple(all_data, \
							tree->tail->prev->data, tree->tail->data);
	data = tree->tail->data;
	for_free = data->content.element;
	stack_pop_back(&parser->tree_stack, 2);
	free(for_free);
	tree_push_back(&parser->tree_stack, content);
	data = parser->tree_stack.tail->data;
	data->tree_type = TREE_CMD;
	return (RV_SUCCESS);
}

// SC -> ELEM;
t_return_value	reduce_rule_9(t_all_data *all_data)
{
	t_parser		*parser;
	t_list			*tree;
	t_tree_data		*data;
	t_tree_content	content;
	t_element		*for_free;

	parser = &all_data->parser;
	stack_pop_back(&parser->parser_stack, 2 * 1);
	parser_push_back(&parser->parser_stack, TT_SIMPLE);
	tree = &parser->tree_stack;
	data = tree->tail->data;
	content.cmd = make_simple(all_data, NULL, tree->tail->data);
	for_free = data->content.element;
	stack_pop_back(&parser->tree_stack, 1);
	free(for_free);
	tree_push_back(&parser->tree_stack, content);
	data = parser->tree_stack.tail->data;
	data->tree_type = TREE_CMD;
	return (RV_SUCCESS);
}
