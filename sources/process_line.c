/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:22:40 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/14 20:22:41 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static t_lexer	*init_lexer(t_lexer *lexer, char *input)
{
	lexer->input = input;
	lexer->current_state = ft_lexer_state(*input);
	if (lexer->current_state == LS_ITEM)
		lexer->last_item = *input;
	else
		lexer->last_item = '\0';
	lexer->index = 1;
	return (lexer);
}

int	process_line(t_all_data *all_data, char *input)
{
	int	return_value;

	if (!(*input))
		return (0);
	add_history(input);
	init_lexer(&all_data->lexer, input);
	list_init(&all_data->token_list);
	if (run_lexer(all_data) < 0)
	{
		ft_putstr_fd("Syntax Error\n", 2);
		return_value = EX_USAGE;
	}
	else if (!(all_data->token_list.head))
	{
		return_value = 0;
	}
	else
	{
		return_value = parse_and_execute(all_data);
	}
	return (return_value);
}
