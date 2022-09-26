/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:22:42 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:26:07 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

int	g_exit_status;

void	prompt_loop(t_all_data *all_data)
{
	char	*line;

	while (1)
	{
		set_prompt_handler();
		line = readline("minishell > ");
		if (line)
		{
			set_handler_for_ignore();
			g_exit_status = process_line(all_data, line);
			free(line);
			line = NULL;
		}
		else
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
	}
}
