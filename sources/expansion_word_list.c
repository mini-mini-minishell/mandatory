#include "../includes/minishell.h"

static void	replace_curr_with_new_list(t_list *new_list, \
		t_word_list **prev)
{
	t_word_list	*last_node;

	if (*prev)
	{
		(*prev)->next = new_list;
	}
	last_node = get_last_node(new_list);
	*prev = last_node;
}

/* typedef  죽여야함*/
typedef enum e_expansion_flag
{
	EXP_NON = 0,
	EXP_VARIABLE = 1 << 1,
	//원래 wordsplit이 2 였던것 , 모르면 교보재 볼것
	EXP_ASTERISK = 1 << 2,
	EXP_QUOT = 1 << 3, 
 	EXP_ALL = EXP_VARIABLE | EXP_ASTERISK | EXP_QUOT
}	t_expansion_flag;

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
