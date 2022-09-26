/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:22:10 by hogkim            #+#    #+#             */
/*   Updated: 2022/09/26 21:25:16 by hogkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/minishell_bonus.h"
#include "../includes_bonus/get_next_line_bonus.h"
#include <stdio.h>
#include <readline/readline.h>
#include <sys/wait.h>

static void	write_free(char *input_line, char *prompt, char *eof)
{
	free(input_line);
	free(prompt);
	free(eof);
}

static void	write_heredoc_to_pipe(t_redir_data *data, int fd)
{
	char			*input_line;
	char			*eof;
	char			*prompt;

	eof = check_heredoc_eof(data->heredoc_eof);
	if (!eof)
		eof = ft_strdup("");
	prompt = ft_strdup("> ");
	while (1)
	{
		input_line = readline(prompt);
		if (!input_line)
			break ;
		if (ft_strncmp(input_line, eof, \
				ft_strlen(data->heredoc_eof) + 1) == 0)
			break ;
		write(fd, input_line, ft_strlen(input_line));
		write(fd, "\n", 1);
		free(input_line);
	}
	ft_close(fd);
	write_free(input_line, prompt, eof);
	exit(0);
}

static void	receive_heredoc_from_pipe(t_redir_data *data, int fd)
{
	char			*doc;
	char			*input_line;

	doc = NULL;
	while (1)
	{
		input_line = get_next_line(fd);
		if (!input_line)
			break ;
		doc = ft_strjoin_gnl(doc, input_line);
		free(input_line);
	}
	data->file_content = doc;
}

static int	fork_receive_heredoc(t_parser *parser, int heredoc_fd[2])
{
	t_heredoc_list	*heredoc_list;
	t_pid			pid;
	int				status;

	heredoc_list = &parser->heredoc_list;
	pid = ft_fork();
	if (pid == 0)
	{
		set_handler_for_heredoc();
		ft_close(heredoc_fd[READ_END]);
		write_heredoc_to_pipe(heredoc_list->head->data, heredoc_fd[WRITE_END]);
	}
	ft_close(heredoc_fd[WRITE_END]);
	set_prompt_handler();
	receive_heredoc_from_pipe(heredoc_list->head->data, heredoc_fd[READ_END]);
	ft_close(heredoc_fd[READ_END]);
	if (waitpid(pid, &status, 0) < 0)
		return (1);
	heredoc_list_remove_head_node(heredoc_list);
	return (get_exit_status(status));
}

int	gather_heredoc(t_parser *parser)
{
	t_heredoc_list	*heredoc_list;
	int				heredoc_fd[2];
	int				exit_status;

	heredoc_list = &parser->heredoc_list;
	exit_status = 0;
	while (heredoc_list->count)
	{
		ft_pipe(heredoc_fd);
		exit_status = fork_receive_heredoc(parser, heredoc_fd);
		if (exit_status != 0)
			break ;
	}
	return (exit_status);
}
