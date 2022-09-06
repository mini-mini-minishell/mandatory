#include "../includes/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// #define S_ISDIR(mode) (((mode) & S_IFMT) == S_IFDIR)

// static int	file_status(char *name)
// {
// 	struct stat	finfo;

// 	if (stat(name, &finfo) < 0)
// 		return (0);
// 	if (S_ISDIR(finfo.st_mode))
// 		return (IS_FILE | IS_DIRECTORY);
// 	return (IS_FILE);
// }

static char	*get_full_path(char *path, char *cmd_name)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp, cmd_name);
	free(temp);
	return (full_path);
	//릭나면 strjoin_gnl로 바꿔
}

// int	is_directory(char *file)
// {
// 	return (file_status(file) & IS_DIRECTORY);
// }

static int	print_err_msg_return_status(int err)
{
	if (err != 0)
	{
		errno = err;
		ft_putstr_fd(": command not found\n", 2); 
		//errno를 좀더 공부하고 에러 메세지 바꾸기!
		return (EX_NOEXEC);
	}
	else
	{
		ft_putstr_fd(": command not found\n", 2);
		//errno를 좀더 공부하고 에러 메세지 바꾸기!
		return (EX_NOTFOUND);
	}
}

static int	try_execute_in_path(char **cmd_array, char **paths, char **env_array)
{
	size_t	index;
	char	*full_path;
	int		err;

	index = 0;
	err = 0;
	while (paths[index])
	{
		full_path = get_full_path(paths[index], cmd_array[0]);
		// if (!is_directory(full_path))
		// {
			execve(full_path, cmd_array, env_array);
			if (errno != ENOENT)
				err = errno;
		// }
		free(full_path);
		++index;
	}
	return (print_err_msg_return_status(err));
}

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
/*chan*/
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

static int	try_direct_execve(char **cmd_array, char **env_array)
{
	// if (is_directory(cmd_array[0]))
	// {
	// 	errno = EISDIR;
	// 	ft_putstr_fd(": directory not found\n", 2);
	// 	return (EXECUTION_FAILURE);
	// }
	execve(cmd_array[0], cmd_array, env_array);
	if (errno == ENOENT)
	{
		ft_putstr_fd(": directory not found\n", 2);
		return (EX_NOTFOUND);
	}
	return (EX_NOEXEC);
}

char	**parse_envp(char **env)
{
	size_t	index;
	char	**result;

	index = 0;
	while (env[index] && ft_strncmp(env[index], "PATH=", 5))
		index++;
	if (!env[index])
		return (NULL);
	result = ft_split(env[index] + 5, ":");
	return (result);
}

static void	free_double(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		++i;
	}
	free(array);
}

static void	free_3_doubles(char **array1, char **array2, char **array3)
{
	free_double(array1);
	free_double(array2);
	free_double(array3);
}

char	*ft_strchr(const char *s, int c)
{
	char	char_c;

	char_c = (char)c;
	while (*s != '\0')
	{
		if (*s == char_c)
 			return ((char *)s);
		s++;
	}
	if (char_c == '\0')
		return ((char *)s);
	else
		return (NULL);
}

int	execute_nonbuiltin(t_cmd *cmd)
{
	char	**argv;
	char	**envp;
	char	**paths;
	int		return_value;

	argv = trans_word_list_2_array(*(cmd->content.simple.words));
	envp = trans_envp_list_2_array(*cmd->envp_list);
	if (ft_strchr(argv[0], '/') == 0)
	{
		paths = parse_envp(envp);
			if (paths)
			{
				return_value = try_execute_in_path(argv, paths, envp);
				free_3_doubles(argv, envp, paths);
				return (return_value);
			}
	}
	return_value = try_direct_execve(argv, envp);
	printf("return_value : %d\n", return_value);
	free_3_doubles(argv, envp, NULL);
	return (return_value);
}
/*
1.리다이렉션을 못알아먹음 + herdoc 시 Close Error 가 나옴
2.pipe를 못알아먹음
3.|| && 를 실행시 minishell 이 종료된다.
expansion 해야하는데 
*/