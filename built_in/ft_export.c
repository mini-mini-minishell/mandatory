#include "../includes/minishell.h"

static char	*extract_key(char *target)
{
	char	*result;
	int		len;

	if (ft_strchr(target, '=') == NULL)
		len = ft_strlen(target);
	else
		len = ft_strchr(target, '=') - target;
	result = ft_malloc(sizeof(char) * (len + 1));
	ft_strlcpy(result, target, len + 1);
	return (result);
}

static t_node	*find_envp_node_by_key(t_cmd *cmd, t_node *current)
{
	char		*key;
	t_node		*target;
	t_word_data	*data;

	data = current->data;
	key = extract_key(data->word);
	target = envp_search_node_by_key(cmd->envp_list, key);
	free(key);
	return (target);
}

static int	set_env(t_cmd *cmd, t_node *current)
{
	t_node		*target;
	t_word_data	*data;

	data = current->data;
	if (isname(data->word)) // 변수명이 될수 있는지 확인.
	{
		target = find_envp_node_by_key(cmd, current);
		if (!target) // target이없다면 새노드 생성하여 붙이기
			list_push_back(cmd->envp_list, cut_and_make_envp_node(data->word));
		else if (ft_strchr(data->word, '='))
		{
			envp_delete_node_by_target(cmd->envp_list, &target);
			list_push_back(cmd->envp_list, cut_and_make_envp_node(data->word));
		}
		return (EXECUTION_SUCCESS);
	}
	else
	{
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(current->data, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (EXECUTION_FAILURE);
	}
}

static int	set_envs(t_cmd *cmd, t_node *current)
{
	int	return_value;

	return_value = EXECUTION_SUCCESS;
	while (current) // 노드를 끝까지 순회하면서 얻고자하는것은?
	{
		if (set_env(cmd, current) == EXECUTION_FAILURE)
			return_value = EXECUTION_FAILURE;
			//if문에 들어왔다면 set_env함수 실패이므로 얼리리턴으로 나가야하지않을까?
		current = current->next;
	}
	return (return_value);
}

int	ft_export(t_cmd *cmd)
{
	t_node		*current;
	t_ex_state	return_value;

	return_value = EXECUTION_SUCCESS;
	if (cmd)
	{
		current = cmd->content.simple.words->head;
		if (current)
			return_value = set_envs(cmd, current);
		// else
			// print_env_sort_by(cmd->env, 1);
	}
	return (return_value);
}
