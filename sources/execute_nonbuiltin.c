#include "../includes/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// static int	print_err_msg_return_status(char *cmd, int err)
// {
// 	char	*err_msg;

// 	if (err != 0)
// 	{
// 		errno = err;
// 		ft_perror(cmd);
// 		return (EX_NOEXEC);
// 	}
// 	else
// 	{
// 		err_msg = ft_strjoin(cmd, ": commmand not found\n");
// 		ft_putstr_fd(err_msg, STDERR_FILENO);
// 		free(err_msg);
// 		return (EX_NOTFOUND);
// 	}
// }

// static char	*get_full_path(char *path, char *cmd_name)
// {
// 	char	*tmp;
// 	char	*full_path;

// 	tmp = ft_strjoin(path, "/");
// 	full_path = ft_strjoin(tmp, cmd_name);
// 	free(tmp);
// 	return (full_path);
// }

// static int	try_execute_in_path(char **cmd_vec, char **paths, char **env_vec)
// {
// 	size_t	idx;
// 	char	*full_path;
// 	int		err;

// 	idx = 0;
// 	err = 0;
// 	while (paths[idx])
// 	{
// 		full_path = get_full_path(paths[idx], cmd_vec[0]);
// 		if (!is_directory(full_path))
// 		{
// 			execve(full_path, cmd_vec, env_vec);
// 			if (errno != ENOENT)
// 				err = errno;
// 		}
// 		free(full_path);
// 		idx++;
// 	}
// 	return (print_err_msg_return_status(cmd_vec[0], err));
// }

// static int	try_direct_execve(char **cmd_vec, char **env_vec)
// {
// 	if (is_directory(cmd_vec[0]))
// 	{
// 		errno = EISDIR;
// 		ft_perror(cmd_vec[0]);
// 		return (EXECUTION_FAILURE);
// 	}
// 	execve(cmd_vec[0], cmd_vec, env_vec);
// 	ft_perror(cmd_vec[0]);
// 	if (errno == ENOENT)
// 		return (EX_NOTFOUND);
// 	return (EX_NOEXEC);
// }

// int	execute_nonbuiltin(t_cmd *cmd)
// {
// 	char	**cmd_vec;
// 	char	**env_vec;
// 	char	**paths;
// 	int		return_value;

// 	if (cmd->content.simple.words->word == NULL)
// 		return (EXECUTION_SUCCESS);
// 	cmd_vec = word_list_to_vector(cmd->content.simple.words);
// 	env_vec = env_list_to_vector(cmd->env);
// 	if (ft_strchr(cmd_vec[0], '/') == 0)
// 	{
// 		paths = parse_envp(env_vec);
// 		if (paths)
// 		{
// 			return_value = try_execute_in_path(cmd_vec, paths, env_vec);
// 			free_vec_multi(cmd_vec, env_vec, paths);
// 			return (return_value);
// 		}
// 	}
// 	return_value = try_direct_execve(cmd_vec, env_vec);
// 	free_vec_multi(cmd_vec, env_vec, NULL);
// 	return (return_value);
// }

//------jaehwanKim-------------
void	error_exit(void)
{
	// perror("\033[32mError");
	exit(EXIT_FAILURE);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

char	*check_access(char *cmd, t_list envp_list)
{
	int		i;
	char	*real_cmd;
	char	*slash_path;
	char	**paths;

	paths = ft_split(envp_search_value(envp_list, "PATH"), ":");
	i = 0;
	while (paths[i] != 0)
	{
		slash_path = ft_strjoin(paths[i], "/");
		real_cmd = ft_strjoin(slash_path, cmd);
		if (access(real_cmd, X_OK) == 0)
		{
			free_paths(paths);
			return (real_cmd);
		}
		free(slash_path);
		free(real_cmd);
		i++;
	}
	return (0);
}

// static int	try_direct_execve(char **cmd_vec, char **env_vec)
// {
// 	if (is_directory(cmd_vec[0]))
// 	{
// 		errno = EISDIR;
// 		ft_perror(cmd_vec[0]);
// 		return (EXECUTION_FAILURE);
// 	}
// 	execve(cmd_vec[0], cmd_vec, env_vec);
// 	ft_perror(cmd_vec[0]);
// 	if (errno == ENOENT)
// 		return (EX_NOTFOUND);
// 	return (EX_NO);
// }

void	execute_nonbuiltin(t_cmd *cmd, t_list envp_list)
{
	char	**argv;
	char	**envp;
	char	*real_cmd;

	argv = trans_word_list_2_array(*(cmd->content.simple.words));
	real_cmd = check_access(argv[0], envp_list);
	envp = trans_envp_list_2_array(envp_list);
	if (real_cmd == 0)
		error_exit();
	if (execve(real_cmd, argv, envp) == -1) //Execve는 실행되고 나서 exit. 이 반환값을 밖에서 받아서(fork 해야함) 170, 171줄 실행할 것.
	{
		if (execve(argv[0], argv, envp))
			printf("cmd not found\n");
	}
}
