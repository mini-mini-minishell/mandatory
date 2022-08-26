#include "../includes/minishell.h"
#include <stdio.h>

/* chanpa
char	*expansion_heredoc_eof(char *orig_str)
{
	t_buffer		new_buffer;
	t_quot_state	quote_flag;

	if (!orig_str)
	{
		return (NULL);
	}
	new_buffer = init_buffer(NULL);
	quote_flag = QUOT_NON;
	while (*orig_str)
	{
		if (quote_flag == check_quote(*orig_str, quote_flag))
			append_char_to_buffer(&new_buffer, *orig_str);
		orig_str++;
	}
	return (new_buffer.word);
}
*/

t_quot_state	check_quote(char word, int quote_flag)
{
	if (word == '\'')
	{
		if (!(quote_flag & QUOT_DOUBLE))
		{
			quote_flag ^= QUOT_SINGLE;
		}
	}
	else if (word == '"')
	{
		if (!(quote_flag & QUOT_SINGLE))
		{
			quote_flag ^= QUOT_DOUBLE;
		}
	}
	return (quote_flag);
}

char	*check_heredoc_eof(char *str)
{
	t_quot_state	quote_flag;
	char			*new_str;
	char			*temp;

	if (!str)
		return (NULL);
	new_str = ft_strdup("");
	while (*str)
	{
		if (quote_flag == check_quote(*str, quote_flag))
		{
			temp = ft_malloc(sizeof(char) * 2);
			temp = ft_strlcpy(temp, str, 2);
			ft_strjoin(new_str, temp);
			free(temp);
		}
		str++;
	}
	return (new_str);
}

static void	write_heredoc_to_pipe(t_list *redir_list, int fd)
{
	t_redir_data	*data;
	char			*input_line;
	char			*eof;
	char			*prompt;

	data = redir_list->head->data;
	eof = check_heredoc_eof(data->heredoc_eof);
	if (!eof)
		eof = ft_strdup("");
	prompt = ft_strdup("> ");
	while (1)
	{
		input_line = readline(prompt);
		if (!input_line)
			break ;
		if (ft_strcmp(input_line, data->heredoc_eof) == 0)
			break ;
		write(fd, input_line, ft_strlen(input_line));
		write(fd, "\n", 1);
		free(input_line);
	}
	ft_close(fd);
	free(input_line);
	free(prompt);
	free(eof);
	exit(0);
}

static int	fork_receive_heredoc(t_parser *parser, int heredoc_fd[2])
{
	t_list			*heredoc_list;
	t_pid			pid;
	int				status;

	heredoc_list = &parser->heredoc_list;
	pid = ft_fork();
	if (pid == 0)
	{
		set_handler_to_heredoc();
		ft_close(heredoc_fd[READ_END]);
		write_heredoc_to_pipe(heredoc_list->redir_list, heredoc_fd[WRITE_END]);
	}
	safe_close(heredoc_fd[WRITE_END]);
	set_prompt_handler();
	receive_heredoc_from_pipe(heredoc_list->redir_list, heredoc_fd[READ_END]);
	safe_close(heredoc_fd[READ_END]);
	if (waitpid(pid, &status, 0) < 0)
		return (1);
	parser->heredoc_list = heredoc_list->next;
	free(heredoc_list);
	return (get_exit_status(status));
}


int	gather_heredoc(t_parser *parser)
{
	int			heredoc_fd[2];
	int			exit_status;

	exit_status = 0;
	while (parser->heredoc_list.count)
	{
		ft_pipe(heredoc_fd);
		exit_status = fork_receive_heredoc(parser, heredoc_fd); // 짜야 함
		if (exit_status != 0)
			break ;
	}
	while (parser->heredoc_list.count)
		list_remove_head_redir(&parser->heredoc_list);
	return (exit_status);
}

/* static void	receive_heredoc_from_pipe(t_redir_list *redir_list, int fd)
{
	char		*doc;
	char		*input_line;
	size_t		doc_len;
	size_t		doc_size;

	doc = NULL;
	doc_size = 0;
	doc_len = 0;
	while (1)
	{
		input_line = get_next_line(fd);
		if (!input_line)
			break ;
		doc = append_string(doc, &doc_len, &doc_size, input_line);
		free(input_line);
	}
	if (doc)
		doc[doc_len] = '\0';
	else
	{
		doc = ft_xmalloc(1);
		doc[0] = '\0';
	}
	redir_list->filename = doc;
}
*/