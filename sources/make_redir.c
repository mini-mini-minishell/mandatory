#include "../includes/minishell.h"
#include <unistd.h>
#include <fcntl.h>

static void	make_redir_in(t_redir_data *data, char *word)
{
	data->redir_type = REDIR_IN;
	data->flag = O_RDONLY;
	data->fd_orig = STDIN_FILENO;
	data->fd_new = -1;
	data->filename = word;
	data->heredoc_eof = NULL;
}

static void	make_redir_out(t_redir_data *data, char *word)
{
	data->redir_type = REDIR_OUT;
	data->flag = O_CREAT | O_WRONLY | O_TRUNC;
	data->fd_orig = STDOUT_FILENO;
	data->fd_new = -1;
	data->filename = word;
	data->heredoc_eof = NULL;
}

static void	make_redir_append(t_redir_data *data, char *word)
{
	data->redir_type = REDIR_APPEND;
	data->flag = O_CREAT | O_WRONLY | O_APPEND;
	data->fd_orig = STDOUT_FILENO;
	data->fd_new = -1;
	data->filename = word;
	data->heredoc_eof = NULL;
}

// quote removal for eof needed
static void	make_redir_heredoc(t_redir_data *data, char *word)
{
	data->redir_type = REDIR_HEREDOC;
	data->flag = 0;
	data->fd_orig = STDIN_FILENO;
	data->fd_new = -1;
	data->filename = NULL;
	data->heredoc_eof = word;
}

t_list	*make_redir(char *word, t_token_type token)
{
	t_list			*redir_list;
	t_redir_data	*data;

	redir_list = ft_malloc(sizeof(t_list));
	list_init(redir_list);
	data = redir_list->tail->data;
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
		data->filename = NULL;
		data->heredoc_eof = NULL;
	}
	return (redir_list);
}