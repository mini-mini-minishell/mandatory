#include "../includes/minishell.h"

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
