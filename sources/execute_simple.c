#include "../includes/minishell.h"
#include <stdio.h>

static int	execute_simple_internal(t_built_in_fp builtin, t_cmd *cmd)
{
	if (builtin)
	{
		list_remove_head_word(cmd->content.simple.words);
		return (builtin(cmd));
	}
	else
		return(execute_nonbuiltin(cmd));
}

static int	execute_with_fork(int is_nullcmd, t_built_in_fp builtin, \
		t_cmd *cmd, int fd_info[3])
{
	pid_t	pid;

	printf("with_fork_man\n");
	pid = ft_fork();
	if (pid == 0)
	{
		set_handler_for_default();
		if (do_redirections(fd_info, cmd->redir_list, cmd->envp_list) < 0)
			exit(EXIT_FAILURE);
		if (is_nullcmd)
			exit(EXIT_SUCCESS);
		exit(execute_simple_internal(builtin, cmd));
	}
	cmd->pid_last_child = pid;
	return (0);
}


static int	execute_without_fork(int is_empty_words, t_built_in_fp builtin, \
		t_cmd *cmd, int fd_info[3])
{
	int	fd_buff[3];
	int	return_value;
	printf("나 without fork 이올씨다 \n");

	printf("without_fork : cmd->redir_list %p\n", cmd->redir_list);
	printf("without_fork : cmd->flag %d\n", cmd->flag);
	printf("이것은 %d\n", cmd->flag & CMD_FLAG_IS_FORKED);
	if (cmd->flag & CMD_FLAG_IS_FORKED)
	{
		printf("파이프 뒤 실행");
		if (do_redirections(fd_info, cmd->redir_list, cmd->envp_list) < 0)
			return (EXECUTION_FAILURE);
		if (is_empty_words)
			return (EXECUTION_SUCCESS);
		return (execute_simple_internal(builtin, cmd));
	}
	else
	{
		save_fd_status(fd_buff);
		if (do_redirections(fd_info, cmd->redir_list, cmd->envp_list) < 0)
			return (restore_fd_status(fd_buff, EXECUTION_FAILURE));
		if (is_empty_words)
			return_value = EXECUTION_SUCCESS;
		else
			return_value = execute_simple_internal(builtin, cmd);
		return (restore_fd_status(fd_buff, return_value));
	}
}

#include <stdio.h>
int	execute_simple(t_cmd *cmd, int fd_info[3])
{
	int				is_empty_words;
	t_built_in_fp	builtin;

	// cmd->content.simple.words = expansion_all(cmd->content.simple.words, \
	// 		cmd->envp_list);
	is_empty_words = (cmd->content.simple.words == NULL);
	builtin = NULL;
	if (!is_empty_words)
		builtin = is_builtin(cmd->content.simple.words);
	//printf("cmd -> flag  : %d\n", cmd->flag);
	if (!is_empty_words && !builtin && !(cmd->flag & CMD_FLAG_IS_FORKED))
		cmd->flag |= CMD_FLAG_NEED_FORK;
	printf("before without_fork : cmd->flag %d\n", cmd->flag);
	if (cmd->flag & CMD_FLAG_NEED_FORK)
		return (execute_with_fork(is_empty_words, builtin, cmd, fd_info));
	else
		return (execute_without_fork(is_empty_words, builtin, cmd, fd_info));
}
