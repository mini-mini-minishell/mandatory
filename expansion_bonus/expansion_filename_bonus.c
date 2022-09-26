/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_filename_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:21:24 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:21:12 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
#include <dirent.h>
#include <stdio.h>

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

static int	add_matched_filenames(t_list *info_new_list, DIR *dirp)
{
	t_word_data		*word_data;
	char			*pattern;
	struct dirent	*dp;
	t_list			*variables;

	word_data = info_new_list->head->data;
	pattern = word_data->word;
	variables = ft_malloc(sizeof(t_list));
	list_init(variables);
	while (1)
	{
		dp = readdir(dirp);
		if (dp == NULL)
			break ;
		pattern_matching(dp, pattern, variables);
	}
	if (variables->head)
	{
		word_list_remove_all(word_data->variables);
		word_data->variables = variables;
		return (1);
	}
	if (!variables->count)
		free(variables);
	return (0);
}

static int	add_filenames_to_variable(t_list *info_new_list)
{
	DIR		*dirp;
	int		return_value;
	t_node	*current;

	return_value = 0;
	dirp = opendir(".");
	if (dirp)
	{
		current = info_new_list->head;
		while (current != NULL)
		{
			return_value += add_matched_filenames(info_new_list, dirp);
			current = current->next;
		}
		closedir(dirp);
	}
	return (return_value);
}

static void	restore_asterisk(t_list *info_new_list)
{
	t_word_data	*word_data;
	t_size		i;

	i = 0;
	if (info_new_list && info_new_list->count)
	{
		word_data = info_new_list->head->data;
		while (word_data->word[i])
		{
			if (word_data->word[i] == '\001')
				word_data->word[i] = '*';
			i++;
		}
	}
}

int	filename_expansion(t_list **info_new_list)
{
	t_word_data	*word_data;
	int			expanded;

	expanded = 0;
	word_data = (*info_new_list)->head->data;
	if ((*info_new_list)->count && word_data->word)
	{
		expanded = add_filenames_to_variable(*info_new_list);
		if (expanded)
		{
			substitute_filename(info_new_list);
		}
		else
		{
			restore_asterisk(*info_new_list);
		}
	}
	return (expanded);
}
