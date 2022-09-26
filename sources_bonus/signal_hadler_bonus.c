/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hadler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:23:02 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:26:26 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>

extern int	g_exit_status;

static void	set_handler_reset_minishline(int sig)
{
	ft_putstr_fd("\n", 1);
	if (sig != 0)
	{
		g_exit_status = 128 + sig;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGINT)
		g_exit_status = 1;
}

void	set_prompt_handler(void)
{
	signal(SIGINT, set_handler_reset_minishline);
	signal(SIGQUIT, SIG_IGN);
}

void	set_handler_for_heredoc(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	set_handler_for_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_handler_for_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}