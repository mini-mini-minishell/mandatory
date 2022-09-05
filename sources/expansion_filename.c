#include "../includes/minishell.h"
#include <dirent.h>

static void	pattern_matching(struct dirent *dp, char *pattern, \
		t_list *variables)
{
	if (match(pattern, dp->d_name) == 1)
	{
		if ((pattern[0] != '.' && dp->d_name[0] != '.') \
				|| (pattern[0] == '.' && dp->d_name[0] == '.'))
			list_push_back(variables, \
				list_new_node(create_word_data(ft_strdup(dp->d_name))));
	}
}

static int	add_matched_filenames(t_list *words, DIR *dirp)
{
	t_word_data		*word_data;
	char			*pattern;
	struct dirent	*dp;
	t_list			*variables;

	word_data = words->head->data;
	pattern = word_data->word;
	variables = NULL;
	while (1)
	{
		dp = readdir(dirp);
		if (dp == NULL)
			break ;
		pattern_matching(dp, pattern, variables);
	}
	if (variables)
	{
		word_list_remove_all(word_data->variables);
		word_data->variables = variables;
		return (1);
	}
	return (0);
}

static int	add_filenames_to_variable(t_list *words)
{
	DIR		*dirp;
	int		return_value;
	t_node	*current;

	return_value = 0;
	dirp = opendir(".");
	if (dirp)
	{
		current = words->head;
		while (current != NULL)
		{
			return_value += add_matched_filenames(words, dirp);
			current = current->next;
		}
		closedir(dirp);
	}
	return (return_value);
}

static void	restore_asterisk(t_list *words)
{
	t_word_data	*word_data;
	size_t		i;

	i = 0;
	if (words && words->count)
	{
		word_data = words->head->data; 
		while (word_data->word[i])
		{
			if (word_data->word[i] == '\001')
				word_data->word[i] = '*';
			i++;
		}
	}
}

int	filename_expansion(t_list **words)
{
	t_word_data	*word_data;
	int			expanded;

	expanded = 0;
	if ((*words)->tail)
	{
		word_data = (*words)->tail->data;
		expanded = add_filenames_to_variable(*words);
		if (expanded)
		{
			substitute_filename(words);
		}
		else
		{
			restore_asterisk(*words);
		}
	}
	return (expanded);
}
