#include "../includes/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

#ifndef MAXIMUM_BYTE
# define MAXIMUM_BYTE 65536
#endif

static int	heredoc_write(int fd, char *document, size_t document_len)
{
	ssize_t	write_return;

	write_return = write(fd, document, document_len);
	if (write_return < 0 || (size_t)write_return != document_len)
		return (-1);
	return (0);
}

static int	open_heredoc_pipe(char *document)
{
	int		fildes[2];
	size_t	document_len;

	if (!document)
		document = "";
	ft_pipe(fildes);
	document_len = ft_strlen(document);
	if (document_len > MAXIMUM_BYTE)
	{
		ft_close(fildes[WRITE_END]);
		ft_close(fildes[READ_END]);
		errno = ENOSPC;//28
		return (-1);
	}
	if (heredoc_write(fildes[WRITE_END], document, document_len) < 0)
	{
		ft_close(fildes[WRITE_END]);
		ft_close(fildes[READ_END]);
		return (-1);
	}
	ft_close(fildes[WRITE_END]);
	return (fildes[READ_END]);
}

static int	heredoc_redir(t_list *word_list)
{
	t_word_data *data;
	int			fd;

	data = word_list->head->data;
	fd = open_heredoc_pipe(data->word);
	word_list_remove_all(word_list);
	if (fd < 0)
	{
		ft_putstr_fd(": fd error\n", STDERR_FILENO);
		return (-1);
	}
	return (fd);
}

static int	normal_redir(t_redir_data *redir_data, t_list *word_list)
{
	t_word_data	*word_data;
	int			fd;

	word_data = word_list->head->data;
	if (word_list->count < 2)
	{
		ft_putstr_fd(redir_data->file_content, STDERR_FILENO);
		ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
		word_list_remove_all(word_list);
		return (-1);
	}
	fd = open(word_data->word, redir_data->flag, 0644);
	if (fd < 0)
	{
		ft_putstr_fd(": file open error\n", 2);
		word_list_remove_all(word_list);
		return (-1);
	}
	word_list_remove_all(word_list);
	return (fd);
}

int	get_redir_fd(t_redir_data *redir_data, t_list *envp_list)
{
	t_list	*word_list;

	// word_list = NULL;
	list_init(word_list);
	list_push_back(word_list, list_new_node(create_word_data(ft_strdup(redir_data->file_content))));
	if (redir_data->redir_type != REDIR_HEREDOC)
	{
		//word_list = expansion_all(word_list, envp_list);
		return (normal_redir(redir_data, word_list));
	}
	else
	{
		// if (!is_quoted(redir_data->heredoc_eof))
		// 	word_list = expansion_heredoc_content(word_list, envp_list);
		if (word_list)
			return (heredoc_redir(word_list));
		// else
		// {
		// 	list_init(word_list);
		// 	return (heredoc_redir(new_word_list(ft_strdup(""))));
		// } //문제가 생기면 바로 다시 만들기
	}
}
