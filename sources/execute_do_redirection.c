#include "../includes/minishell.h"
// #include <unistd.h>
// #include <stdlib.h>
// #include <fcntl.h>
#include <stdio.h>

static int	dup2_pipe(int fd_info[3])
{
	if (fd_info[CLOSE_END] > 0)
		ft_close(fd_info[CLOSE_END]);
	if (fd_info[READ_END] > 0)
	{
		if (ft_dup2(fd_info[READ_END], STDIN_FILENO) < 0)
			return (-1);
		ft_close(fd_info[READ_END]);
	}

	if (fd_info[WRITE_END] > 0)
	{
		if (ft_dup2(fd_info[WRITE_END], STDOUT_FILENO) < 0)
			return (-1);
		ft_close(fd_info[WRITE_END]);
	}
	return (0);
}


static int	dup2_redir_list(t_list *redir_list, t_list *envp_list)
{
	t_redir_data	*redir_data;
	t_node			*current;
	
	current = redir_list->head;
	// printf("redir head, count %p %zu-----------\n", current, redir_list->count);
	while (current)
	{
		redir_data = current->data;
		redir_data->fd_new = get_redir_fd(redir_data, envp_list);
		if (redir_data->fd_new < 0)
			return (-1);
		if (ft_dup2(redir_data->fd_new, redir_data->fd_orig) < 0)
			return (-1);
		ft_close(redir_data->fd_new);
		current = current->next;
	}
	return (0);
}


// int	get_redir_fd(t_redir_list *redir_list, t_env_list *env)
// {
// 	t_word_list	*word_list;

// 	word_list = new_word_list(ft_strdup(redir_list->filename));
// 	if (redir_list->redir_type != REDIR_HEREDOC)
// 	{
// 		// word_list = expansion_all(word_list, env);
// 		return (normal_redir(redir_list, word_list));
// 	}
// 	else
// 	{
// 		if (!is_quoted(redir_list->heredoc_eof))
// 		{
// 			word_list = expansion_heredoc_content(word_list, env);
// 		}
// 		if (word_list)
// 		{
// 			return (heredoc_redir(word_list));
// 		}
// 		else
// 		{
// 			return (heredoc_redir(new_word_list(ft_strdup(""))));
// 		}
// 	}
// }

// static int	dup2_redir_list(t_redir_list *redir_list, t_env_list *env)
// {
// 	while (redir_list)
// 	{
// 		redir_list->fd_new = get_redir_fd(redir_list, env);
// 		if (redir_list->fd_new < 0)
// 		{
// 			return (-1);
// 		}
// 		if (safe_dup2(redir_list->fd_new, redir_list->fd_orig) < 0)
// 		{
// 			return (-1);
// 		}
// 		safe_close(redir_list->fd_new);
// 		redir_list = redir_list->next;
// 	}
// 	return (0);
// }

int	do_redirections(int fd_info[3], t_list *redir_list, t_list *env)
{
	if (dup2_pipe(fd_info) < 0)
		return (-1);
	if (dup2_redir_list(redir_list, env) < 0)
		return (-1);
	fd_info[READ_END] = NO_PIPE;
	fd_info[WRITE_END] = NO_PIPE;
	fd_info[CLOSE_END] = NO_PIPE;
	return (0);
}
