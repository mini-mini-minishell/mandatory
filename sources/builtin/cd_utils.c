#include "../includes/minishell.h"
#include <stdlib.h>

int	which_directory_word(t_cmd *cmd, char *target)
{
	char		*word;
	t_word_data	*data;
	int			return_value;

	data = cmd->content.simple.words->tail->data;
	word = data->word;
	return_value = ft_strncmp(target, word, 2);
	return (return_value);
}

//함수 이름 고민,,
int	bind_variable(t_cmd *cmd, char *pwd, char *key)
{
	t_node	*envp_node;

	envp_node = where_in_envp_list(cmd->envp_list, key);
	if (envp_node)
		envp_delete_node(cmd->envp_list, ???index???);
		//index,,,,,, [envp_search_value] 함수 응용?
		//아니면 OLDPWD key는 그대로 두고 value 값만 바꾸기?
	list_push_back(cmd->envp_list, list_new_node(create_envp_data(key, pwd)));
	envp_node = where_in_envp_list(cmd->envp_list, key);
	if (envp_node)
	{
		ft_perror("cd: set variable failed");
		//error 처리?
		return (0);
	}
	return (1);
}

//함수 이름 고민,,
static int	bind_pwd_free_pwdvar(t_cmd *cmd, char *pwd_variable, char *target)
{
	int	return_value;

	return_value = EXECUTION_SUCCESS;
	if (pwd_variable)
	{
		if (!bind_variable(cmd, pwd_variable, target))
			return_value = EXECUTION_FAILURE;
	}
	else if (!pwd_variable)
		return_value = 2;
		//?????
	free(pwd_variable);
	return (return_value);
}

//함수 이름 고민,,
static char	*get_cwd_fallback_envlist(char *buf, size_t size, t_cmd *cmd)
{
	char	*cwd_name;

	cwd_name = getcwd(buf, size);
	//buf가 NULL일 경우, 함수 안에서 말록해서 버퍼 넘겨줌.
	if (!cwd_name)
		cwd_name = ft_strdup(find_envp_value(cmd->envp_list, "PWD"));
		//그냥 처음부터 이렇게 쓰면 안 됨?
	return (cwd_name);
}

//함수 이름 고민,,
int	bind_cwd_to(char *target, t_cmd *cmd)
{
	int		return_value;
	char	*pwd_variable;

	pwd_variable = get_cwd_fallback_envlist(NULL, 0, cmd);
	return_value = bind_pwd_free_pwdvar(cmd, pwd_variable, target);
	return (return_value);
}
