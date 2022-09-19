/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_envp2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:22:21 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/14 20:22:22 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

t_env_data	*create_envp_data(char *key, char *value)
{
	t_env_data	*new;

	new = ft_malloc(sizeof(t_env_data));
	new->key = key;
	new->value = value;
	return (new);
}

void	envp_free_node(t_node **node)
{
	t_env_data	*temp_data;

	temp_data = (t_env_data *)((*node)->data);
	free(temp_data->key);
	free(temp_data->value);
	free(temp_data);
	free(*node);
}

void	envp_delete_node(t_list *list, t_size index)
{
	t_size	i;
	t_node	*temp;
	t_node	*current;

	if (index == 0)
	{
		temp = list->head;
		list->head = temp->next;
		--(list->count);
	}
	else if (list->count == index)
		temp = list_pop_back(list);
	else
	{
		current = list->head;
		i = 0;
		while (i++ < index - 1)
			current = current->next;
		temp = current->next;
		current->next = temp->next;
		--(list->count);
	}
	envp_free_node(&temp);
}
