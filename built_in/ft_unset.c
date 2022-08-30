#include "../includes/minishell.h"

// void	delete_target_env_node(t_list *envp_list, char *key)
// {
// 	t_node		*current;
// 	size_t		index;
// 	size_t		key_len;
// 	t_env_data	*temp_data;

// 	if (!envp_list->count)
// 		return ;
// 	key_len = ft_strlen(key);
// 	current = envp_list->head;
// 	index = 0;
// 	while (index < envp_list->count)
// 	{
// 		temp_data = current->data;
// 		if (!ft_strncmp(key, temp_data->key, key_len + 1))
// 			envp_delete_node(envp_list, index);	
// 		current = current->next;
// 		++index;
// 	}
// }

int	ft_unset(t_cmd *cmd)
{
	t_node		*current;
	t_node		*target;
	t_word_data *data;

	current = cmd->content.simple.words->head;
	while (current)
	{
		data = current->data;
		if (!data->word)
			return (EXECUTION_SUCCESS);
		else
		{
			target = envp_search_node_by_key(cmd->envp_list, data->word);
			envp_delete_node_by_target(cmd->envp_list, &target);	
		}
		current = current->next;
	}
	return (EXECUTION_SUCCESS);
}
