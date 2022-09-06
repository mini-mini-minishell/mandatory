#include "../includes/minishell.h"

static int	is_pattern(char *target)
{
	size_t	i;
	int		quote_flag;

	i = 0;
	quote_flag = QUOT_NON;
	while (target[i] != '\0' && target[i] != '\001')
	{
		quote_flag = check_quote(target[i], quote_flag);
		i++;
	}
	return (target[i] == '\001' && quote_flag == QUOT_NON);
}
/*  */
// struct s_expansion_info	
// {
// 	// t_buffer		curr_word; //주서끄
// 	char			*curr_word;
// 	t_list			*new_list;
// 	t_quot_state	quote_flag;
// };
// /*  */

#include <stdio.h>
void	substitute_filename(t_list **info_new_addr)
{
	t_word_data	*word_data;
	t_node		*curr;
	t_list		*temp_list;

	curr = (*info_new_addr)->head;
	if (curr)
	{
		temp_list = ft_malloc(sizeof(t_list));
		list_init(temp_list);
		while (curr)
		{
			word_data = curr->data;
			if (is_pattern(word_data->word) && word_data->variables)
			{
				while (word_data->variables->count)
					list_push_back(temp_list, list_pop_head(word_data->variables));
				free(word_data->variables);
			}
			curr = curr->next;
		}
		if (temp_list->count)
		{
			word_list_remove_all(*info_new_addr);
			*info_new_addr = temp_list;
		}
		else
			free(temp_list);
	}
}

/* chan */

// static void	free_word_list_except_variables(t_word_list **words)
// {
// 	t_word_list	*curr;

// 	curr = *words;
// 	while (curr)
// 	{
// 		*words = curr;
// 		curr = curr->next;
// 		free((*words)->word);
// 		free(*words);
// 	}
// }

// void	substitute_filename(t_word_list **words)
// {
// 	t_word_list	*curr;
// 	t_word_list	*new_list;

// 	curr = *words;
// 	if (curr)
// 	{
// 		new_list = NULL;
// 		while (curr)
// 		{
// 			if (is_pattern(curr->word) && curr->variables)
// 			{
// 				addback_word_list(curr->variables, &new_list);
// 			}
// 			curr = curr->next;
// 		}
// 		if (new_list)
// 		{
// 			curr = *words;
// 			free_word_list_except_variables(&curr);
// 			*words = new_list;
// 		}
// 	}
// }
