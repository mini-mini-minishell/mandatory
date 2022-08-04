#include "../includes/minishell.h"
#include <stdlib.h>
// t_env_data	*

static void	envp_free_node(t_node **node)
{
	t_env_data	*temp_data;

	temp_data = (t_env_data *)((*node)->data);
	free(temp_data->key);
	free(temp_data->value);
	free(temp_data);
	free(*node);
}

void	envp_delete_node(t_list *list, int index)
{
	int		i;
	t_node	*temp;
	t_node	*current;

	if (index == 0)
	{
		temp = list->head;
		list->head = temp->next;
		--(list->count);
	}
	else if (list->count == index)
		temp = list_pop_back(list);
	else
	{
		current = list->head;
		i = 0;
		while (i < index - 1)
		{
			current = current->next;
			++i;
		}
		temp = current->next;
		current->next = temp->next;
		--(list->count);
	}
	envp_free_node(&temp);
}

int	envp_search_node(t_list *list, char *key)
{
	int			index;
	t_node		*current;
	size_t		key_len;
	t_env_data	*temp_data;

	if (!list->count)
		return (-1);
	key_len = ft_strlen(key);
	current = list->head;
	temp_data = (t_env_data *)(current->data);
	index = 0;
	while (index < list->count)
	{
		if (ft_strncmp(key, temp_data->key, key_len + 1))
			return (index);
		current = current->next;
		++index;
	}
	return (-1);
}

static void	get_envp_list(t_list *envp_list, char **envp)
{
	t_node		*new_node; // node 생성 함수
	t_env_data	*new;
	int			index;
	char		**current_envp;

	index = 0;
	while(envp[index])
	{
		new = malloc(sizeof(t_env_data));
		if (!new)
			exit_with_message("Memory Error");
		current_envp = ft_split(envp[index], "=");
		new->key = current_envp[0];
		new->value = current_envp[1];
		list_push_back(envp_list, new);
		free(current_envp);
		++index;
	}
}

void	get_envp(t_all_lists *all_lists, char **envp)
{
	t_list	envp_list;

	envp_list = all_lists->envp_list;
	list_init(&envp_list);
	get_envp_list(&envp_list, envp);
}
