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
