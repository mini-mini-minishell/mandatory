/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:22:24 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/19 13:37:32 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void	parser_push_back(t_list *list, int type)
{
	void	*data;
	t_node	*new_node;

	data = create_parser_data(type);
	new_node = list_new_node(data);
	list_push_back(list, new_node);
}

void	tree_push_back(t_list *list, t_tree_content content)
{
	void	*data;
	t_node	*new_node;

	data = create_tree_data(content);
	new_node = list_new_node(data);
	list_push_back(list, new_node);
}

t_parser_data	*create_parser_data(int type)
{
	t_parser_data	*new_data;

	new_data = ft_malloc(sizeof(t_parser_data));
	if (type & PARSER_STATE)
	{
		new_data->type = PARSER_STATE;
		new_data->state = type;
	}
	else
	{
		new_data->type = 0;
		new_data->token = type;
	}
	return (new_data);
}

t_tree_data	*create_tree_data(t_tree_content content)
{
	t_tree_data	*new_data;

	new_data = ft_malloc(sizeof(t_tree_data));
	new_data->content = content;
	return (new_data);
}
