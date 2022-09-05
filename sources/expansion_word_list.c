#include "../includes/minishell.h"

// static void	replace_curr_with_new_list(t_list *new_list, \
// 		t_list **prev)
// {
// 	t_list	*last_node;

// 	if (*prev)
// 	{
// 		(*prev)->next = new_list;
// 	}
// 	last_node = get_last_node(new_list);
// 	*prev = last_node;
// }

t_list	*expand_word_list(t_list *words, t_list *env, \
		t_expansion_flag flag)
{
	t_node		*curr;
	t_node		*next;
	t_list		*new_list;
	t_list		*temp;

	curr = words->head;
	new_list = NULL;
	while (curr != NULL)
	{
		next = curr->next;
		temp = expand_one_node(curr->data, env, flag);
		if (new_list)
		{
			temp->head->prev = new_list->tail;
			new_list->tail = temp->tail;
			new_list->tail->next = temp->head;
			new_list->count += temp->count;
			free(temp);
		}
		else
			new_list = temp;
		free(curr->data);
		free(curr);
		curr = next;
	}
	free(words);
	return (new_list);
}
