#include "../includes/minishell.h"

// static int	execute_simple_internal(t_builtin_funcs builtin, t_cmd *cmd)
// {
	// t_word_list		*words;

	// if (builtin)
	// {
	// 	words = cmd->content.simple.words;
	// 	cmd->content.simple.words = cmd->content.simple.words->next;
	// 	free(words->word);
	// 	free(words);
	// 	return (builtin(cmd));
	// }
	// else
// 		return (execute_nonbuiltin(cmd));
// }

// static int	execute_with_fork(int is_nullcmd, t_builtin_funcs builtin, \
// 		t_cmd *cmd, int fd_info[3])
// {
// 	pid_t	pid;

// 	pid = safe_fork();
// 	if (pid == 0)
// 	{
// 		set_handler_to_default();
// 		if (do_redirections(fd_info, cmd->redir_list, cmd->env) < 0)
// 			exit(EXIT_FAILURE);
// 		if (is_nullcmd)
// 			exit(EXIT_SUCCESS);
// 		exit(execute_simple_internal(builtin, cmd));
// 	}
// 	cmd->pid_last_child = pid;
// 	return (0);
// }

// static int	execute_without_fork(int is_nullcmd, t_builtin_funcs builtin, \
// 		t_cmd *cmd, int fd_info[3])
// {
// 	int	fd_buff[3];
// 	int	return_value;

// 	if (cmd->flag & CMD_FLAG_IS_FORKED)
// 	{
// 		if (do_redirections(fd_info, cmd->redir_list, cmd->env) < 0)
// 			return (EXECUTION_FAILURE);
// 		if (is_nullcmd)
// 			return (EXECUTION_SUCCESS);
		// return (execute_simple_internal(builtin, cmd));
// 	}
// 	else
// 	{
// 		save_fd_status(fd_buff);
// 		if (do_redirections(fd_info, cmd->redir_list, cmd->env) < 0)
// 			return (restore_fd_status(fd_buff, EXECUTION_FAILURE));
// 		if (is_nullcmd)
// 			return_value = EXECUTION_SUCCESS;
// 		else
// 			return_value = execute_simple_internal(builtin, cmd);
// 		return (restore_fd_status(fd_buff, return_value));
// 	}
// }

// int	execute_simple(t_cmd *cmd, int fd_info[3])
// {
	//int				is_nullcmd;
	// t_builtin_funcs	builtin;

	// cmd->content.simple.words = expansion_all(cmd->content.simple.words, \
	// 		cmd->env);
	// is_nullcmd = (cmd->content.simple.words == NULL);
	// builtin = NULL;
	// if (!is_nullcmd)
	// {
	// 	builtin = is_builtin(cmd->content.simple.words->word);
	// }
	// if (!is_nullcmd && !builtin && !(cmd->flag & CMD_FLAG_IS_FORKED))
	// {
	// 	cmd->flag |= CMD_FLAG_NEED_FORK;
	// }
	// if (cmd->flag & CMD_FLAG_NEED_FORK)
	// {
	// 	return (execute_with_fork(is_nullcmd, builtin, cmd, fd_info));
	// }
	// else
	// {
	//	return (execute_without_fork(is_nullcmd, builtin, cmd, fd_info));
	// }
// }
