#include "../includes/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

#ifndef F_GETPIPE_SZ
# define F_GETPIPE_SZ 65536
#endif

static int	heredoc_write(int fd, char *document, size_t document_len)
{
	ssize_t	write_return;

	write_return = write(fd, document, document_len);
	if (write_return < 0 || (size_t)write_return != document_len)
	{
		return (-1);
	}
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
	if (document_len > F_GETPIPE_SZ)
	{
		ft_close(fildes[WRITE_END]);
		ft_close(fildes[READ_END]);
		errno = ENOSPC;
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

static int	heredoc_redir(t_node *word_node)
{
	int	fd;

	fd = open_heredoc_pipe(word_list->word);
	free_word_list(word_list);
	if (fd < 0)
	{
		ft_perror("heredoc");
		return (-1);
	}
	return (fd);
}

static int	normal_redir(t_redir_data *redir_data, t_node *word_node)
{
	int			fd;
	t_word_data	*word_data;

	word_data = word_node->data;
	if (*(word_data->word) ==  || word_node->next != NULL)
	{
		ft_putstr_fd(redir_data->file_content, STDERR_FILENO);
		ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
		free_word_list(word_node);
		return (-1);
	}
	fd = open(word_data->word, redir_data->flag, 0644);
	if (fd < 0)
	{
		ft_perror(word_data->word);
		free_word_list(word_list);
		return (-1);
	}
	free_word_list(word_node);
	return (fd);
}

int	get_redir_fd(t_redir_data *redir_data, t_list *envp_list)
{
	t_list	*word_list;

	// word_list = NULL;
	list_init(word_list);
	list_push_back(word_list, create_word_data(ft_strdup(redir_data->file_content)));
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
		else
			return (heredoc_redir(new_word_list(ft_strdup(""))));
	}
}