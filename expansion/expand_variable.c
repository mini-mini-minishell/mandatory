/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:21:22 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/27 19:57:18 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	substitute_asterisk(char *value)
{
	t_size	i;

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

static void	do_variable_expansion(char *value, t_expansion_info *info)
{	
	if (info->quote_flag == QUOT_NON)
		substitute_asterisk(value);
	expand_variable_nosplit(value, &info->curr_word, &(info->new_list));
}

void	update_last_node_word(t_list *new_list, char *curr_word)
{
	t_word_data	*last_word_data;

	if (new_list->count)
	{
		last_word_data = new_list->tail->data;
		last_word_data->word = curr_word;
	}
	else
	{
		list_push_back(new_list, list_new_node(create_word_data(curr_word)));
	}
}

static void	if_no_value(t_expansion_info *info, char **word, char *name)
{
	char	*temp;

	if (name)
	{
		if (info->quote_flag != QUOT_NON)
		{
			temp = ft_strjoin_free(info->curr_word, ft_strdup(""));
			update_last_node_word(info->new_list, temp);
		}
	}
	else
	{
		if (!ft_strlen(*word) || ft_strlen(info->curr_word))
		{
			temp = ft_strjoin_free(info->curr_word, ft_strdup("$"));
			info->curr_word = temp;
		}
		else
		{
			temp = ft_strjoin("$", info->curr_word);
			info->curr_word = temp;
		}
		update_last_node_word(info->new_list, temp);
	}	
}

void	expand_variable(char **word, t_list *env, t_expansion_info *info)
{
	char	*name;
	char	*value;

	++(*word);
	name = NULL;
	value = get_expanded_string(env, word, &name);
	if (value)
		do_variable_expansion(value, info);
	else
		if_no_value(info, word, name);
	if (name)
		free(name);
}
