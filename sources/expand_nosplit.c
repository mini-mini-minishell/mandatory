#include "../includes/minishell.h"

int	expand_variable_nosplit(char *value, char *curr_word, t_list **new_list)
{
	t_word_data	*data;

	if ((*new_list)->tail)
	{
		data = (*new_list)->tail->data;
		data->word = curr_word;
	}
	return (0);
}
