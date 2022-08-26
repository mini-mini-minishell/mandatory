#include "../includes/minishell.h"
#include <stdio.h>

//---------------------chanha!
struct s_redir_list
{
	t_redir_list	*next;
	t_redir_type	redir_type;
	int				flag;
	int				fd_orig;
	int				fd_new;
	char			*filename;
	char			*heredoc_eof;
};

// struct s_heredoc_list
// {
// 	t_heredoc_list	*next;
// 	t_redir_list	*redir_list;
// };
//--------------------------

struct s_redir_data
{
	t_redir_type	redir_type;
	int				flag;
	int				fd_orig;
	int				fd_new;
	char			*filename;
	char			*heredoc_eof;
};

struct s_parser
{
	t_reducer_fp	reduce_func[22];
	t_list			parser_stack;
	t_list			tree_stack;
	t_list			heredoc_list;
	t_cmd			*final_cmd;
	t_parser_flag	flag;
}; 

int	gather_heredoc(t_parser *parser)
{
	int			heredoc_fd[2];
	int			exit_status;

	exit_status = 0;
	while (parser->heredoc_list.count)
	{
		safe_pipe(heredoc_fd);
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

static void	write_heredoc_to_pipe(t_redir_list *redir_list, int fd)
{
	char		*input_line;
	char		*eof;
	char		*prompt;

	eof = expansion_heredoc_eof(redir_list->heredoc_eof);
	if (!eof)
		eof = ft_strdup("");
	prompt = ft_strjoin(eof, ": heredoc> ");
	while (1)
	{
		input_line = readline(prompt);
		if (!input_line)
			break ;
		if (ft_strcmp(input_line, eof) == 0)
			break ;
		write(fd, input_line, ft_strlen(input_line));
		write(fd, "\n", 1);
		free(input_line);
	}
	safe_close(fd);
	free(input_line);
	free(prompt);
	free(eof);
	exit(0);
}

static int	fork_receive_heredoc(t_parser *parser, int fildes[2])
{
	t_heredoc_list	*heredoc_list;
	pid_t			pid;
	int				status;

	heredoc_list = parser->heredoc_list;
	pid = safe_fork();
	if (pid == 0)
	{
		set_handler_to_heredoc();
		safe_close(fildes[READ_END]);
		write_heredoc_to_pipe(heredoc_list->redir_list, fildes[WRITE_END]);
	}
	safe_close(fildes[WRITE_END]);
	set_prompt_handler();
	receive_heredoc_from_pipe(heredoc_list->redir_list, fildes[READ_END]);
	safe_close(fildes[READ_END]);
	if (waitpid(pid, &status, 0) < 0)
		return (1);
	parser->heredoc_list = heredoc_list->next;
	free(heredoc_list);
	return (get_exit_status(status));
}

int	gather_heredoc(t_parser *parser)
{
	int				fildes[2];
	int				exit_status;
	t_heredoc_list	*heredoc_list;

	exit_status = 0;
	while (parser->heredoc_list)
	{
		safe_pipe(fildes);
		exit_status = fork_receive_heredoc(parser, fildes);
		if (exit_status != 0)
			break ;
	}
	while (parser->heredoc_list)
	{
		heredoc_list = parser->heredoc_list;
		parser->heredoc_list = heredoc_list->next;
		free(heredoc_list);
	}
	return (exit_status); 
}
*/