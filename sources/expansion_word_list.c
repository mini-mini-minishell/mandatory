#include "../includes/minishell.h"
#include <stdio.h>

t_list	*expand_word_list(t_list *words, t_list *env, \
		t_expansion_flag flag)
{
	t_node		*current;
	t_node		*next;
	t_list		*new_list;
	t_list		*temp;

	current = words->head;
	new_list = NULL;
	while (current != NULL)
	{
		next = current->next;
		temp = expand_one_node(current, env, flag);
		if (new_list)
		{
			new_list->tail->next = temp->head;
			temp->head->prev = new_list->tail;
			new_list->tail = temp->tail;
			new_list->count += temp->count;
			free(temp);
		}
		else
			new_list = temp;
		free(current->data);
		free(current); //remove_head로 바꿔야 함?
		current = next;
	}
	free(words);
	return (new_list);
}
