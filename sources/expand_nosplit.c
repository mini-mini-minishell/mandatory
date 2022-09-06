#include "../includes/minishell.h"
#include <stdio.h>

int	expand_variable_nosplit(char *value, char *curr_word, t_list **info_new_addr)
{
	t_word_data	*data;
	char		*prev_word;

	if ((*info_new_addr)->tail)
	{
		data = (*info_new_addr)->tail->data;
		prev_word = data->word;
		data->word = ft_strjoin(prev_word, value);
	}
	else
	{
		// curr_word = ft_strjoin(curr_word, value);
		list_push_back(*info_new_addr, list_new_node(create_word_data(ft_strjoin(curr_word, value))));
	}
	if (curr_word)
		free(curr_word);
	if (value)
		free(value);
	return (0);
}
