#include "../includes/minishell.h"
#include <unistd.h>
#include <fcntl.h>

static void	make_redir_in(t_redir_data *data, char *word)
{
	data->redir_type = REDIR_IN;
	data->flag = O_RDONLY;
	data->fd_orig = STDIN_FILENO;
	data->fd_new = -1;
	data->file_content = word;
	data->heredoc_eof = NULL;
}

static void	make_redir_out(t_redir_data *data, char *word)
{
	data->redir_type = REDIR_OUT;
	data->flag = O_CREAT | O_WRONLY | O_TRUNC;
	data->fd_orig = STDOUT_FILENO;
	data->fd_new = -1;
	data->file_content = word;
	data->heredoc_eof = NULL;
}

static void	make_redir_append(t_redir_data *data, char *word)
{
	data->redir_type = REDIR_APPEND;
	data->flag = O_CREAT | O_WRONLY | O_APPEND;
	data->fd_orig = STDOUT_FILENO;
	data->fd_new = -1;
	data->file_content = NULL;
	data->heredoc_eof = word;
}

// quote removal for eof needed
static void	make_redir_heredoc(t_redir_data *data, char *word)
{
	data->redir_type = REDIR_HEREDOC;
	data->flag = 0;
	data->fd_orig = STDIN_FILENO;
	data->fd_new = -1;
	data->file_content = NULL;
	data->heredoc_eof = word;
}

#include <stdio.h>

t_node	*make_redir_node(char *word, t_token_type token)
{
	t_node			*new_node;
	t_redir_data	*data;

	new_node = list_new_node(create_redir_data());
	data = new_node->data;
	if (token == TT_REDIR_IN)
		make_redir_in(data, word);
	else if (token == TT_REDIR_OUT)
		make_redir_out(data, word);
	else if (token == TT_REDIR_APPEND)
		make_redir_append(data, word);
	else if (token == TT_REDIR_HEREDOC)
		make_redir_heredoc(data, word);
	else
	{
		data->redir_type = REDIR_NON;
		data->flag = 0;
		data->fd_orig = -1;
		data->fd_new = -1;
		data->file_content = NULL;
		data->heredoc_eof = NULL;
	}
	return (new_node);
}