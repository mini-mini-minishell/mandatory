/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:20:28 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:19:14 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
#include <stdio.h>

static int	check_opt(t_list *list)
{
	t_word_data	*word_data;

	if (!list->head)
		return (1);
	word_data = list->head->data;
	if (word_data->word && !ft_strncmp(word_data->word, "-n", 3))
		return (0);
	return (1);
}

static void	print_echo(t_node *current, t_word_data *word_data)
{
	if (current->next)
		printf("%s ", word_data->word);
	else
		printf("%s", word_data->word);
}

int	ft_echo(t_cmd *cmd)
{
	int			display_return;
	t_list		*word_list;
	t_node		*current;
	t_word_data	*word_data;

	word_list = cmd->content.simple.words;
	if (!word_list->head)
	{
		printf("\n");
		return (EXECUTION_SUCCESS);
	}
	word_data = word_list->head->data;
	display_return = check_opt(word_list);
	current = word_list->head;
	if (!display_return)
		current = current->next;
	while (current && word_data->word)
	{
		word_data = current->data;
		print_echo(current, word_data);
		current = current->next;
	}
	if (display_return)
		printf("\n");
	return (EXECUTION_SUCCESS);
}
