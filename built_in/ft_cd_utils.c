#include "../includes/minishell.h"
#include <stdlib.h>

int	check_one_word(t_cmd *cmd, const char target)
{
	char		*word;
	t_word_data	*data;

	data = cmd->content.simple.words->head->data;
	word = data->word;
	return (word[0] == target && word[1] == '\0');
}

int	do_replace(t_cmd *cmd, char *pwd, char *key)
{
	t_node	*envp_node;

	envp_node = envp_search_node_by_key(cmd->envp_list, key);
	if (envp_node)
		envp_delete_node_by_target(cmd->envp_list, &envp_node);
	list_push_back(cmd->envp_list, list_new_node(create_envp_data(key, ft_strdup(pwd))));
	if (!envp_search_node_by_key(cmd->envp_list, key))
	{
		ft_putstr_fd("cd: set variable failed\n", 2);
		return (0);
	}
	return (1);
} // OLDPWD(key)=pwd or PWD(key)=pwd

static int	check_and_replace(t_cmd *cmd, char *pwd, char *key)
{
	int	return_value;

	return_value = EXECUTION_SUCCESS;
	if (pwd)
	{
		if (!do_replace(cmd, pwd, key))
			return_value = EXECUTION_FAILURE;
		free(pwd);
	}
	else if (!pwd)
		return_value = 2;
	return (return_value);
}

int	replace_pwd(char *key, t_cmd *cmd)
{
	int		return_value;
	char	*pwd;
	
	//export에서 존재하는 환경변수 치환과 같은 함수로 가도 좋을 듯!
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup(envp_search_value(*cmd->envp_list, "PWD"));
	return_value = check_and_replace(cmd, pwd, key);
	return (return_value);
}
