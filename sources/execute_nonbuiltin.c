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

static int	try_direct_execve(char **cmd_array, char **env_array)
{
	// if (is_directory(cmd_array[0]))
	// {
	// 	errno = EISDIR;
	// 	ft_putstr_fd(": directory not found\n", 2);
	// 	return (EXECUTION_FAILURE);
	// }
	execve(cmd_array[0], cmd_array, env_array);
	ft_putstr_fd(": directory not found\n", 2);
	if (errno == ENOENT)
		return (EX_NOTFOUND);
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
	char	*real_cmd;
	char	**paths;
	int		return_value;

	argv = trans_word_list_2_array(*(cmd->content.simple.words));
	real_cmd = check_access(argv[0], *cmd->envp_list);
	envp = trans_envp_list_2_array(*cmd->envp_list);
	if (!real_cmd)
		return (EXECUTION_SUCCESS);
	printf("%c \n", *(ft_strchr(real_cmd, '/')));
	if (ft_strchr(argv[0], '/') == 0) //의심!!!!!!!! == 0 뭔가 이상하다
	{
		paths = parse_envp(envp);
		printf("path : %p \n", paths);
			if (paths)
			{
				return_value = try_execute_in_path(argv, paths, envp);
				free_3_doubles(argv, envp, paths);
				return (return_value);
			}
	}
	return_value = try_direct_execve(argv, envp);
	free_3_doubles(argv, envp, NULL);
	return (return_value);
}
