#include "../includes/minishell.h"

static void	substitute_asterisk(char *value)
{
	size_t	i;

	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '*')
		{
			value[i] = '\001';
		}
		i++;
	}
}

static void	do_variable_expansion(char *value, t_expansion_flag flag, \
			t_expansion_info *info)
{	
	if (info->quote_flag == QUOT_NON)
		substitute_asterisk(value);
	expand_variable_nosplit(value, info->curr_word, &(info->new_list));
	// free(value);
}

void	update_last_node_word(t_list *new_list, char *curr_word)
{
	t_word_data	*last_word_data;

	if (new_list->count)
	{
		last_word_data = new_list->tail->data;
		// last_word_data->word = ft_strjoin
		//					(last_word_data->word,curr_word);
		last_word_data->word = curr_word;
	}
	else
	{
		list_push_back(new_list, list_new_node(create_word_data(curr_word)));
	}
}

void	expand_variable(char **word, t_list *env, t_expansion_flag flag, \
		t_expansion_info *info)
{
	char	*name;
	char	*value;
	char	*temp;

	++(*word);
	name = NULL;
	value = get_expanded_string(env, word, &name);
	// $단어 셋트를 밸류로 바까주기만함.
	if (value)
	{
		do_variable_expansion(value, flag, info);
		free(name);
	}
	else if (name)
	{
		free(name);
		if (info->quote_flag != QUOT_NON)
		{
			temp = ft_strjoin(info->curr_word, ft_strdup(""));
			update_last_node_word(info->new_list, temp);
		}
	}
	else
	{
		temp = ft_strjoin(ft_strdup("$"), info->curr_word);
		update_last_node_word(info->new_list, temp);
	}
}
