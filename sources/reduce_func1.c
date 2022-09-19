/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_func1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:22:45 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/14 20:22:46 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

// S -> L;
t_return_value	reduce_rule_0(t_all_data *all_data)
{
	int			count;
	t_parser	*parser;
	t_tree_data	*tree_data;

	parser = &all_data->parser;
	tree_data = parser->tree_stack.tail->data;
	count = 2 * 1;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_back(&parser->parser_stack, TT_START);
	parser->flag = PARSER_FINISH;
	parser->final_cmd = tree_data->content.cmd;
	return (RV_SUCCESS);
}

// L -> L && P;
t_return_value	reduce_rule_1(t_all_data *all_data)
{
	int				count;
	t_parser		*parser;
	t_tree_content	content;
	t_tree_data		*data;
	t_node			*tail;

	parser = &all_data->parser;
	count = 2 * 3;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_back(&parser->parser_stack, TT_LIST);
	tail = parser->tree_stack.tail;
	content.cmd = make_connect(all_data, tail->prev->prev->data, \
								tail->data, tail->prev->data);
	stack_pop_back(&parser->tree_stack, 3);
	tree_push_back(&parser->tree_stack, content);
	data = parser->tree_stack.tail->data;
	data->type = TREE_CMD;
	return (RV_SUCCESS);
}

// L -> P;
t_return_value	reduce_rule_2(t_all_data *all_data)
{
	int				count;
	t_parser		*parser;
	t_tree_content	content;
	t_tree_data		*p;
	t_tree_data		*data;

	parser = &all_data->parser;
	count = 2 * 1;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_back(&parser->parser_stack, TT_LIST);
	p = parser->tree_stack.tail->data;
	content.cmd = p->content.cmd;
	stack_pop_back(&parser->tree_stack, 1);
	tree_push_back(&parser->tree_stack, content);
	data = parser->tree_stack.tail->data;
	data->type = TREE_CMD;
	return (gather_heredoc(parser));
}

// P -> P | C;
t_return_value	reduce_rule_3(t_all_data *all_data)
{
	int				count;
	t_parser		*parser;
	t_tree_content	content;
	t_tree_data		*data;
	t_node			*tail;

	parser = &all_data->parser;
	count = 2 * 3;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_back(&parser->parser_stack, TT_PIPELINE);
	tail = parser->tree_stack.tail;
	content.cmd = make_connect(all_data, tail->prev->prev->data, \
								tail->data, tail->prev->data);
	stack_pop_back(&parser->tree_stack, 3);
	tree_push_back(&parser->tree_stack, content);
	data = parser->tree_stack.tail->data;
	data->type = TREE_CMD;
	return (RV_SUCCESS);
}

// P -> C;
t_return_value	reduce_rule_4(t_all_data *all_data)
{
	int				count;
	t_parser		*parser;
	t_tree_content	content;
	t_tree_data		*p;
	t_tree_data		*data;

	parser = &all_data->parser;
	count = 2 * 1;
	stack_pop_back(&parser->parser_stack, count);
	parser_push_back(&parser->parser_stack, TT_PIPELINE);
	p = parser->tree_stack.tail->data;
	content.cmd = p->content.cmd;
	stack_pop_back(&parser->tree_stack, 1);
	tree_push_back(&parser->tree_stack, content);
	data = parser->tree_stack.tail->data;
	data->type = TREE_CMD;
	return (RV_SUCCESS);
}
