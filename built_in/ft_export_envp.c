/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:20:41 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/14 20:20:41 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*envp_search_node_by_key(t_list *list, char *key)
{
	t_node		*current;
	t_size		key_len;
	t_env_data	*temp_data;

	if (!list->count)
		return (NULL);
	key_len = ft_strlen(key);
	current = list->head;
	while (current)
	{
		temp_data = current->data;
		if (!ft_strncmp(key, temp_data->key, key_len + 1))
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	envp_delete_node_by_target(t_list *list, t_node **target)
{
	if (list->count == 1)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else if (list->head == *target)
	{
		list->head = (*target)->next;
		list->head->prev = NULL;
	}
	else if (list->tail == *target)
	{
		list->tail = (*target)->prev;
		list->tail->next = NULL;
	}
	else
	{
		(*target)->prev->next = (*target)->next;
		(*target)->next->prev = (*target)->prev;
	}
	--(list->count);
	envp_free_node(target);
}

t_node	*cut_and_make_envp_node(char *str)
{
	t_env_data	*data;
	char		**key_and_value;

	key_and_value = ft_split(str, "=");
	data = create_envp_data(key_and_value[0], key_and_value[1]);
	return (list_new_node(data));
}
