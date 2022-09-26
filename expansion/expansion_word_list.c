/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_word_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:21:33 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:12:00 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	join_new_list(t_list *new_list, t_list *temp)
{
	new_list->tail->next = temp->head;
	temp->head->prev = new_list->tail;
	new_list->tail = temp->tail;
	new_list->count += temp->count;
}

static void	free_expand_word_list(t_word_data *word_data, t_node *current)
{
	free(word_data->word);
	free(word_data->variables);
	free(current->data);
	free(current);
}

t_list	*expand_word_list(t_list *words, t_list *env, \
		t_expansion_flag flag)
{
	t_node		*current;
	t_node		*next;
	t_list		*new_list;
	t_list		*temp;
	t_word_data	*word_data;

	current = words->head;
	new_list = NULL;
	while (current != NULL)
	{
		next = current->next;
		temp = expand_one_node(current, env, flag);
		if (new_list)
		{
			join_new_list(new_list, temp);
			free(temp);
		}
		else
			new_list = temp;
		word_data = current->data;
		free_expand_word_list(word_data, current);
		current = next;
	}
	free(words);
	return (new_list);
}
