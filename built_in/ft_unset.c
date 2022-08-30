#include "../includes/minishell.h"

void	delete_target_env_node(t_list *envp_list, char *key)
{
	t_node		*current;
	size_t		index;
	size_t		key_len;
	t_env_data	*temp_data;

	if (!envp_list->count)
		return ;
	key_len = ft_strlen(key);
	current = envp_list->head;
	index = 0;
	while (index < envp_list->count)
	{
		temp_data = current->data;
		if (!ft_strncmp(key, temp_data->key, key_len + 1))
			envp_delete_node(envp_list, index);	
		current = current->next;
		++index;
	}
}

int	ft_unset(t_all_data *all_data, t_cmd *cmd)
{
	t_list		*word_list;
	t_node		*current;
	t_word_data *target;
	
	word_list = cmd->content.simple.words;
	current = word_list->head;
	while (current != NULL)
	{
		target = current->data;
		if (target->word == NULL)
			return (EXECUTION_SUCCESS);
		else
			delete_target_env_node(&all_data->envp_list, target->word);
		current = current->next;
	}
	return (EXECUTION_SUCCESS);
}
