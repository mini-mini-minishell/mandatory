#include "../includes/minishell.h"

static void	envp_free_node(t_node **node)
{
	free((*node)->((t_env_data *)data)->key);
	free((*node)->((t_env_data *)data)->value);
	free((*node)->((t_env_data *)data));
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
	int		index;
	t_node	*current;
	size_t	key_len;

	if (!list->count)
		return (-1);
	key_len = ft_strlen(key);
	current = list->head;
	index = 0;
	while (index < list->count)
	{
		if (ft_strncmp(key, current->((t_env_data *)data)->key, key_len + 1))
			return (index);
		current = current->next;
		++index;
	}
	return (-1);
}
