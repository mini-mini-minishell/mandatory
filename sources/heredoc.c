#include "../includes/minishell.h"
#include "../includes/get_next_line.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdio.h>

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
			ft_strlcpy(temp, str, 2);
			ft_strjoin(new_str, temp);
			free(temp);
			temp = NULL;
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
		if (ft_strncmp(input_line, data->heredoc_eof, ft_strlen(data->heredoc_eof) + 1) == 0)
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

static void	receive_heredoc_from_pipe(t_list *redir_list, int fd)
{
	t_redir_data	*data;
	char			*doc;
	char			*input_line;

	doc = NULL;
	while (1)
	{
		input_line = get_next_line(fd);
		if (!input_line)
			break ;
		doc = ft_strjoin(doc, input_line);
		// doc = append_string(doc, &doc_len, &doc_size, input_line);
		free(input_line);
	}
	data = redir_list->head->data;
	data->file_content = doc;
}

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
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
		set_handler_for_heredoc(1); //+++++++++++++++++++++++++++++++++
		ft_close(heredoc_fd[READ_END]);
		write_heredoc_to_pipe(&parser->heredoc_list, heredoc_fd[WRITE_END]);
	}
	ft_close(heredoc_fd[WRITE_END]);
	set_prompt_handler(1); //++++++++++++++++++++++++++++++++++++
	receive_heredoc_from_pipe(&parser->heredoc_list, heredoc_fd[READ_END]);
	ft_close(heredoc_fd[READ_END]);
	if (waitpid(pid, &status, 0) < 0)
		return (1);
	list_remove_head_redir(heredoc_list);
	// parser->heredoc_list = heredoc_list->next;
	// free(heredoc_list);
	return (get_exit_status(status));
}

int	gather_heredoc(t_parser *parser)
{
	int			heredoc_fd[2];
	int			exit_status;

	exit_status = 0;
	printf("-----------------------0\n");
	printf("count : %d\n", parser->heredoc_list.count);
	while (parser->heredoc_list.count)
	{
		ft_pipe(heredoc_fd);
	printf("-----------------------1\n");
		exit_status = fork_receive_heredoc(parser, heredoc_fd); // 짜야 함
	printf("-----------------------2\n");
		if (exit_status != 0)
			break ;
	}
	printf("-----------------------3\n");
	while (parser->heredoc_list.count)
	{
	printf("-----------------------5\n");
		list_remove_head_redir(&parser->heredoc_list);
	printf("-----------------------6\n");
	}
	printf("-----------------------7\n");
	return (exit_status);
}
